package ltrgo

/*
#cgo CFLAGS: -g -w
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

func (m *CommonModule) setSlot(i int) {
	m.slot = i
}

func (m *CommonModule) setCrate(serial [C.LTR_CRATE_SERIAL_SIZE]C.char) {
	m.crate = serial
}

type ModuleInterface interface {
	Start() error
	GetFrame() (int64, []float32, error) //Возвращает время в мс с начала эпохи и массив измерений
	setSlot(int)
	setCrate([C.LTR_CRATE_SERIAL_SIZE]C.char)
	Stop() error
}
