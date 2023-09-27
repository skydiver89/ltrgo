package main

/*
#cgo CFLAGS: -g -Wall
#cgo LDFLAGS: -L/usr/lib/ -lltrapi -lltr11api -lltr27api -lltr43api
#include <ltr/include/ltrapi.h>
#include <ltr/include/ltrapidefine.h>
#include <ltr/include/ltr11api.h>
#include <ltr/include/ltr27api.h>
#include <ltr/include/ltr43api.h>
*/
import (
	"C"
)
import (
	"errors"
	"log"
	"unsafe"
)

var ErrInit = errors.New("can't initialize ltr structure")
var ErrOpen = errors.New("can't open connection to ltrd")
var ErrGetCrates = errors.New("can't get crates")

func GetCrateSerials() ([]string, error) {
	ltr := new(C.TLTR)
	res := C.LTR_Init(ltr)
	if res != C.LTR_OK {
		return nil, ErrInit
	}

	res = C.LTR_Open(ltr)
	if res != C.LTR_OK {
		return nil, ErrOpen
	}
	foundCrates := 0
	foundCratesPtr := (*C.uint)(unsafe.Pointer(&foundCrates))
	cratesReturned := 0
	cratesReturnedPtr := (*C.uint)(unsafe.Pointer(&cratesReturned))
	var infoList [C.LTR_CRATES_MAX]C.TLTR_CRATE_INFO
	infoListPtr := (*C.TLTR_CRATE_INFO)(unsafe.Pointer(&infoList))
	var serials [C.LTR_CRATES_MAX][C.LTR_CRATE_SERIAL_SIZE]C.char
	res = C.LTR_GetCratesEx(ltr, C.LTR_CRATES_MAX, C.LTR_GETCRATES_FLAGS_WORKMODE_ONLY, foundCratesPtr, cratesReturnedPtr, &serials[0], infoListPtr)
	if res != C.LTR_OK {
		return nil, ErrGetCrates
	}
	C.LTR_Close(ltr)
	var result []string
	for i := 0; i < foundCrates; i++ {
		result = append(result, C.GoString(&serials[i][0]))
	}
	return result, nil
}

func main() {
	crates, err := GetCrateSerials()
	if err != nil {
		log.Fatalln(err)
	}
	log.Println(crates)
}
