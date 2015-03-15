// Format https://twitter.com/search to tsv.
package tw

import (
    "fmt"
    "os"
    "log"
    "strconv"
    "strings"
    "time"
    "github.com/PuerkitoBio/goquery"
)

const tfOut = "2006-01-02 15:04:06"

func HtmlToTsv(f *os.File) string {
    str := ""

    doc, e := goquery.NewDocumentFromReader(f)
    if e != nil {
        log.Fatal(e)
    }

    doc.Find(".content").Each(func(i int, s *goquery.Selection) {
        header := s.Find(".stream-item-header")
        //name := header.Find(".username").Text()
        name := header.Find(".fullname").Text()
        if name == "" {
            return
        }
        if name[0] != '\'' {
            name = "'" + name
        }

        text := s.Find(".tweet-text").Text()
        if text[0] != '\'' {
            text = "'" + text
        }

        ts2 := header.Find("._timestamp")
        ms, _ := ts2.Attr("data-time")
        ms64, _ := strconv.ParseInt(ms, 10, 64)
        t := time.Unix(ms64, 0)
        timestamp := t.Format(tfOut)

        ts := header.Find(".tweet-timestamp")
        url, _ := ts.Attr("href")

        str = str + fmt.Sprintf("\"%s\"\t\"%s\"\t%s\t%s\n",
            strings.Replace(name, "\"", "\"\"", -1),
            strings.Replace(text, "\"", "\"\"", -1),
            timestamp, url)
    })

    return str
}