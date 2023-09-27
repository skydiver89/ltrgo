package main

/*
#cgo CFLAGS: -g -Wall
#cgo LDFLAGS: -L/usr/lib/ -lltrapi
#include <ltr/include/ltrapi.h>
*/
import (
	"C"
)

var moduleCreator = map[uint8]func() ModuleInterface{
	11: func() ModuleInterface { return &LTR11Module{} },
	27: func() ModuleInterface { return &LTR27Module{} },
	43: func() ModuleInterface { return &LTR43Module{} },
}

type CommonModule struct {
	crate [C.LTR_CRATE_SERIAL_SIZE]C.char
	slot  int
}

func (m *CommonModule) SetSlot(i int) {
	m.slot = i
}

func (m *CommonModule) SetCrate(serial [C.LTR_CRATE_SERIAL_SIZE]C.char) {
	m.crate = serial
}

type ModuleInterface interface {
	Init()
	GetFrame()
	SetSlot(int)
	SetCrate([C.LTR_CRATE_SERIAL_SIZE]C.char)
}
