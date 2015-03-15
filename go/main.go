// Format https://twitter.com/search to tsv.
package main

import (
    "fmt"
    "io"
    "log"
    "os"
    "path/filepath"
    "tw"
)

const defExt = ".txt"

func main() {
    inName := ""
    outName := ""

    args := os.Args
    argv := len(args)
    for i := 0; i < argv; i++ {
        arg := args[i]
        if i == 1 {
            inName = arg
        } else if i == 2 {
            outName = arg
        }
    }
    if inName == "" {
        fmt.Println("Options:")
        fmt.Println("  input filename")
        fmt.Println("  output filename or stdout [optional]")
        return
    }

    f, e := os.Open(inName)
    if e != nil {
        log.Fatal(e)
    }
    defer f.Close()

    str := tw.HtmlToTsv(f)

    if outName == "" {
        ext := filepath.Ext(inName)
        outName = inName[0:len(inName)-len(ext)]
        if ext == defExt {
            outName = outName + "_out"
        }
        outName = outName + defExt
    }

    isStdout := outName == "stdout"
    if isStdout {
        fmt.Println(str)
    } else {
        of, e := os.Create(outName)
        if e != nil {
            log.Fatal(e)
        }
        defer of.Close()

        _, e2 := io.WriteString(of, str)
        if e2 != nil {
            log.Fatal(e2)
        }
    }
}