const Generator = require('./index');

const C = require('const');

class RulesMK extends Generator {

	loadTemplate() { return require('./templates/rules.mk'); }

	fillTemplate() {
		const keyboard = this.keyboard;

		let mcu;
		switch (keyboard.controller) {
			case C.CONTROLLER_ATMEGA32U2: mcu = 'atmega32u2'; break;
			case C.CONTROLLER_ATMEGA32U4: mcu = 'atmega32u4'; break;
			case C.CONTROLLER_AT90USB1286: mcu = 'at90usb1286'; break;
		}

		let bootloaderSize;
		switch (keyboard.settings.bootloaderSize) {
			case C.BOOTLOADER_512: bootloaderSize = '512'; break;
			case C.BOOTLOADER_2048: bootloaderSize = '2048'; break;
			case C.BOOTLOADER_4096: bootloaderSize = '4096'; break;
			case C.BOOTLOADER_8192: bootloaderSize = '8192'; break;
		}

		let chooseBootMagic;
		switch (keyboard.settings.chooseBootMagic) {
			case C.BootMagic_yes: chooseBootMagic = 'yes'; break;
			case C.BootMagic_no: chooseBootMagic = 'no'; break;
			case C.BootMagic_lite: chooseBootMagic = 'lite'; break;
		}

		return {
			'mcu': mcu,
			'bootloader_size': bootloaderSize,
			'use_backlight': keyboard.pins.led ? 'yes' : 'no',
			'use_rgb': keyboard.pins.rgb ? 'yes' : 'no' ,
			'chooseBootMagic': chooseBootMagic
		};
	}

}

module.exports = RulesMK;
