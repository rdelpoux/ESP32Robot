/*
 * moteur.cpp
*
 *  Created on: 11 sept. 2016
 *  Last Modification: 26 Janv. 2020
 *      Author: Florian Bianco (florian.bianco@univ-lyon1.fr)
 *              Romain Delpoux (romain.delpoux@insa-lyon.fr)
 */
 
#include <Arduino.h>

#include "moteur.hpp"
#include "types.h"

Moteur::Moteur() {

  this->pin_pwm = 0;
  this->channel_pwm = 0;
	this->pin_sens = 0;
	this->friction = 0;
	this->vel = 0.0f;
	this->state = STATE_INIT;

}

Moteur::Moteur(int pin_pwm, int channel_pwm, int pin_sens, bool sens, int friction) {

	this->config(pin_pwm, channel_pwm, pin_sens, sens, friction);
}


Moteur::~Moteur() {

}

void Moteur::config(int pin_pwm, int channel_pwm, int pin_sens, bool sens, int friction) {

	this->pin_pwm = pin_pwm;
	this->channel_pwm = channel_pwm;
	this->pin_sens = pin_sens;
	this->friction = friction;
	this->sens = sens;


	/* Set pins */
  pinMode(pin_pwm, OUTPUT);
  ledcAttachPin(pin_pwm, channel_pwm);
  ledcSetup(channel_pwm, 500, 8); // 500Hz PWM, 8-bit resolution
	pinMode(pin_sens, OUTPUT);

	//analogWrite(this->pin_pwm, 0);
	if (sens) {
		digitalWrite(this->pin_sens, HIGH);
	} else {
		digitalWrite(this->pin_sens, LOW);
	}


	/* Motor OK */
	this->state = STATE_OK;

}

void Moteur::run() {

	if (this->state == STATE_OK || this->state == STATE_STOP) {
		this->state = STATE_RUN;
	}
}

void Moteur::stop() {
	ledcWrite(this->channel_pwm, 0);
	this->state = STATE_STOP;
}

void Moteur::commande(float com) {
	float x, out;

	if (this->state != STATE_RUN) {
		return;
	}
  
	if (com >= 0) {
		if (this->sens) {
			digitalWrite(this->pin_sens, HIGH);
		} else {
			digitalWrite(this->pin_sens, LOW);
		}
	} else {
		if (this->sens) {
			digitalWrite(this->pin_sens, LOW);
		} else {
			digitalWrite(this->pin_sens, HIGH);
		}
	}


	this->vel = fabs(255.0/7.0*com) + this->friction;

  //Serial.println(this->vel);
	if (this->vel <= this->friction) {
		this->vel = 0.0f;
	}
	if (this->vel >= 255.0f) {
		this->vel = 255.0f;
	}

	//Serial.print((byte) this->vel);
	ledcWrite(this->channel_pwm,(byte) this->vel);
}



bool Moteur::get_sens() {
	return this->sens;
}
