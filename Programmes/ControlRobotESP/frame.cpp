/*
 * frame.cpp
*
 *  Created on: 11 sept. 2016
 *  Last Modification: 27 fev. 2017
 *      Author: Florian Bianco (florian.bianco@univ-lyon1.fr)
 *              Romain Delpoux (romain.delpoux@insa-lyon.fr)
 */
 

#include <Arduino.h>

#include "frame.hpp"

/* Constructor */
Frame::Frame(WiFiClient * cli) {
  client = cli;
	this->clear();

	this->size_frame = 0;
	this->size_frame += sizeof(this->data.Mark);
	this->size_frame += sizeof(this->data.Id);
	this->size_frame += sizeof(this->data.Cmd);
	this->size_frame += sizeof(this->data.TabData);
	this->size_frame += sizeof(this->data.CheckSum);
}

/* Destructor */
Frame::~Frame() {
	this->data.Id = 0;
	this->data.Cmd = CMD_INIT;

	memset(this->data.TabData, 0, sizeof(s32) * SIZE_TAB_DATA);

	this->data.CheckSum = 0;
}

void Frame::clear() {
	this->data.Mark = MARKER;
	this->data.Id = 0;
	this->data.Cmd = CMD_INIT;

	memset(this->data.TabData, 0, sizeof(s32) * SIZE_TAB_DATA);

	this->data.CheckSum = 0;
}

/* Setters */
void Frame::set_Id(u8 Id) {
	this->data.Id = Id;
}

void Frame::set_Cmd(u8 Cmd) {
	this->data.Cmd = Cmd;
}

void Frame::set_Data(s32 data, int pos) {

	if (pos < 0 || pos >= SIZE_TAB_DATA) {
		return;
	}

	this->data.TabData[pos] = data;
}

void Frame::set_Checksum(u8 Checksum) {
	this->data.CheckSum = Checksum;
}

/* Getters */
u8 Frame::get_Id() {
	return this->data.Id;
}

u8 Frame::get_Cmd() {
	return this->data.Cmd;
}

s32 Frame::get_data(int pos) {
	return this->data.TabData[pos];
}

u8 Frame::get_Checksum() {
	return this->data.CheckSum;
}

u8 * Frame::p_get_Id() {
	return &this->data.Id;
}

u8 * Frame::p_get_Cmd() {
	return &this->data.Cmd;
}

s32 * Frame::p_get_data() {
	return this->data.TabData;
}

u8 * Frame::p_get_Checksum() {
	return &this->data.CheckSum;
}

int Frame::get_sizeFrame() {
	int size = 0;

	size += get_sizeMark();
	size += get_sizeId();
	size += get_sizeCmd();
	size += get_sizeData();
	size += get_sizeCheckSum();

	return size;
}

int Frame::get_sizeMark() {
	return sizeof(data.Mark);
}

int Frame::get_sizeId() {
	return sizeof(data.Id);
}

int Frame::get_sizeCmd() {
	return sizeof(data.Cmd);
}

int Frame::get_sizeData() {
	return sizeof(data.TabData);
}
int Frame::get_sizeCheckSum() {
	return sizeof(data.CheckSum);
}

/* CheckSum */
u8 Frame::calc_checksum() {
	u8 CheckSum;
	u8 * p_data;
	unsigned int i;

	//Init Value
	CheckSum = 0;

	//Calc Value
	CheckSum += this->data.Mark;
	CheckSum += this->data.Id;
	CheckSum += this->data.Cmd;

	p_data = (u8 *) this->data.TabData;
	for(i=0; i < sizeof(u32) * SIZE_TAB_DATA; i++) {
		CheckSum += *(p_data + i);
	}
  Serial.print("Check sum =");
  Serial.println(CheckSum);

	return CheckSum;
}

void Frame::set_checksum() {
	this->data.CheckSum = this->calc_checksum();
}

bool Frame::verif_checksum() {
	bool retval = false;
	u8 checksum;

	checksum = this->calc_checksum();

	if (checksum == this->data.CheckSum) {
		retval = true;
	}

	return retval;
}

Data_Frame * Frame::create_data_frame() {
	int i;
	Data_Frame * data = NULL;

	data = (Data_Frame *) malloc(sizeof(Data_Frame));
	if (data == NULL) {
		return NULL;
	}

	data->Id = this->get_Id();
	data->Cmd = this->get_Cmd();
	data->CheckSum = this->get_Checksum();

	for(i=0; i < SIZE_TAB_DATA; i++) {
		data->TabData[i] = this->get_data(i);
	}

	return data;
}

void Frame::send_frame() {
	unsigned int i, j;
	u8 * p_data;
	u8 data[4];

	client->write((char *) &this->data.Mark, this->get_sizeMark());
	client->write((char *) &this->data.Id, this->get_sizeId());
	client->write((char *) &this->data.Cmd, this->get_sizeCmd());


	for(i=0; i < SIZE_TAB_DATA; i++) {
		p_data = (u8 *) &this->data.TabData[i];


		//client.write((char *) p_data, sizeof(s32));

		for(j = 0; j < 4; j++) {
			data[j] = *(p_data + j);

		}
		client->write(data, 4);
	}

	client->write((char *) &this->data.CheckSum, this->get_sizeCheckSum());
 Serial.println("frame send");
}

bool Frame::recev_frame() {
	u8 Mark, Id, Cmd, data8, Checksum;
	s32 data32;
	unsigned int i, j;
	int nbr_read;
	bool retval = false;
  //Serial.println("Recev_Frame");
	nbr_read = client->available();

	/*
	if (nbr_read > 0) {
		Serial.print("DATA IN  = ");
		Serial.print(nbr_read);
		Serial.print("\n");
	}
	*/
	if (nbr_read < this->get_sizeFrame()) {
		return false;
	}

	//Serial.print("READ Frame - ");
	//Serial.print(nbr_read);
	//Serial.print("\n");


	Mark = client->read();

	//Serial.print(Mark, HEX);


	if (Mark != MARKER) {
		return false;
	}

	Id = client->read();
	Cmd = client->read();

	for(i=0; i < SIZE_TAB_DATA; i++) {
		data32 = 0;
		for(j=0; j < sizeof(s32); j++) {
			data8 = client->read();
			data32 += data8 << (8*j);
		}
		this->set_Data(data32, i);
	}

	Checksum = client->read();

	this->set_Id(Id);
	this->set_Cmd(Cmd);
	this->set_Checksum(Checksum);

	retval = this->verif_checksum();

	this->print();

	return retval;
}

void Frame::print() {
	u8 * p_data;
	unsigned int i, j;

	//print values
	Serial.print("\n");
	Serial.print(this->data.Mark, HEX);
	Serial.print("-");
	Serial.print(this->data.Id, HEX);
	Serial.print("-");
	Serial.print(this->data.Cmd, HEX);
	Serial.print("-");

	for(i=0; i < SIZE_TAB_DATA; i++) {
		p_data = (u8 *) &this->data.TabData[i];
		for(j=0; j < sizeof(u32); j++) {
			Serial.print(*(p_data + j), HEX);
			Serial.print(" ");
		}
		Serial.print("-");
	}

	Serial.print(this->data.CheckSum, HEX);
	Serial.print("\n");
}
