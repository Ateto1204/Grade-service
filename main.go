package main

import (
	"fmt"
	"strings"

	"github.com/Ateto1204/Grade-service/controller"
)

func main() {

	for {
		// get line from std
		getline := controller.ReadFromStdin()
		if getline == "end" {
			break
		}

		// split input by whitespace
		split := strings.Fields(getline)
		cmd := split[0]
		if cmd == "add" {
			if len(split) != 3 {
				fmt.Println("Invalid input!")
				continue
			}

		}
	}
}
