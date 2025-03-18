/*
 * moteur.hpp
*
 *  Created on: 11 sept. 2016
 *   Last Modification: 26 Janv. 2020
 *      Author: Florian Bianco (florian.bianco@univ-lyon1.fr)
 *              Romain Delpoux (romain.delpoux@insa-lyon.fr)
 */
 
#ifndef MOTEUR_HPP_
#define MOTEUR_HPP_

class Moteur {
private:

	int pin_pwm;
  int channel_pwm;
	int pin_sens;
	int friction;
	bool sens;

	/* State */
	int state;

	float vel;

public:
	Moteur();
	Moteur(int pin_pwm, int channel_pwm, int pin_sens, bool sens, int friction);
	~Moteur();

	/* Note : sens : determine si le sens de rotation pour avance / recule */
	void config(int pin_pwm, int channel_pwm, int pin_sens, bool sens, int friction);

	void run();
	void stop();

	bool get_sens();

	void commande(float com);


};


#endif /* MOTEUR_HPP_ */
