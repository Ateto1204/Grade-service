package controller

import (
	"bufio"
	"os"
)

var (
	reader = bufio.NewReader(os.Stdin)
)

func ReadFromStdin() string {
	result, _ := reader.ReadString('\n')
	witl := result[:len(result)-1]
	return witl
}
