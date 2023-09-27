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
	var serials [C.LTR_CRATES_MAX]string
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
	//serialsPtr := (*[C.LTR_CRATES_MAX]C.char)(unsafe.Pointer(&serials))
	//serialsPtr := make([]*C.char, C.LTR_CRATES_MAX)
	//var serialsPtr *[C.LTR_CRATES_MAX]C.char
	var infoList [C.LTR_CRATES_MAX]C.TLTR_CRATE_INFO
	infoListPtr := (*C.TLTR_CRATE_INFO)(unsafe.Pointer(&infoList))
	var cstrs [C.LTR_CRATES_MAX]C.char

	//var cstrs *[C.LTR_CRATES_MAX]C.char
	res = C.LTR_GetCratesEx(ltr, C.LTR_CRATES_MAX, C.LTR_GETCRATES_FLAGS_WORKMODE_ONLY, foundCratesPtr, cratesReturnedPtr, &cstrs, infoListPtr)
	log.Println(C.GoString(&cstrs[0]))
	if res != C.LTR_OK {
		return nil, ErrGetCrates
	}
	for i := 0; i < foundCrates; i++ {
		//log.Println(serialsPtr)
		log.Println(cstrs[i])
		//log.Println(serials[i])
	}
	C.LTR_Close(ltr)
	var result []string
	for i := 0; i < 16; i++ {
		if serials[i] != "" {
			result = append(result, serials[i])
		}
	}
	return result, nil
}

func main() {
	_, err := GetCrateSerials()
	if err != nil {
		log.Fatalln(err)
	}
}
