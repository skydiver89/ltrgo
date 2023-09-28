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
	//fmt.Println(crates)
	var allModules []ModuleInterface
	for _, crate := range crates {
		fmt.Println(crate)
		modules, err := GetModules(crate)
		if err != nil {
			log.Fatalln(err)
		}
		allModules = append(allModules, modules...)
	}
	if len(allModules) == 0 {
		log.Fatalln("No modules found")
	}
	for _, module := range allModules {
		module.Start()
	}
	for i := 0; i < 100; i++ {
		allModules[0].GetFrame()
	}
	for _, module := range allModules {
		module.Stop()
	}
}
