package main

import (
 "fmt"
 "time"
)

type Pos struct {
  x int
  y int
}

func main() {

    beginTs := makeTimestamp()

    fmt.Printf("Begin\n")


    endTs := makeTimestamp()

    fmt.Printf("End. Elapsed time = %d ms \n", endTs - beginTs)
}
