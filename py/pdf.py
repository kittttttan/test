#!usr/bin/env python
# -*- coding: utf-8 -*- 

# http://www.reportlab.com/software/opensource/rl-toolkit/
from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.cidfonts import UnicodeCIDFont
from reportlab.lib.units import cm

def main():
    pdfFile = canvas.Canvas("./sample.pdf")
    pdfFile.saveState()

    pdfFile.setAuthor("kittttttan")
    pdfFile.setTitle("PDF生成")
    pdfFile.setSubject("サンプル")

    #    A4
    width, height = 21.0*cm, 29.7*cm
    #    B5
    #width, height = 18.2*cm, 25.7*cm
    pdfFile.setPageSize((width, height))

    # line
    pdfFile.setLineWidth(1)
    pdfFile.line(7*cm, 21*cm, 14*cm, 7*cm)

    # rect
    pdfFile.setFillColorRGB(0, 0, 100)
    pdfFile.rect(3*cm, 3*cm, 7*cm, 7*cm, stroke=1, fill=1)
    pdfFile.setFillColorRGB(0,0,0)

    # string
    pdfmetrics.registerFont(UnicodeCIDFont("HeiseiKakuGo-W5"))
    pdfFile.setFont("HeiseiKakuGo-W5", 12)
    pdfFile.drawString(7*cm, height - 3*cm, "１２３４５６奈々ー！")

    pdfFile.restoreState()
    pdfFile.save()

if __name__ == "__main__":
    main()

