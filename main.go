package main

import (
	"fmt"
	"log"
)

func main() {
	crates, err := GetCrateSerials()
	if err != nil {
		log.Fatalln(err)
	}
	fmt.Println(crates)
	var allModules []ModuleInterface
	for _, crate := range crates {
		modules, err := GetModules(crate)
		if err != nil {
			log.Fatalln(err)
		}
		allModules = append(allModules, modules...)
	}
	fmt.Println(len(allModules))
}
