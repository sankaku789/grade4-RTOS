
#let fonts = yaml("config.yaml").font-setting
#let settings = yaml("config.yaml").document-setting
#let meta = yaml("config.yaml").document-meta 

// 書式設定を行う関数
#let setup(
  seriffont: fonts.serif-font, 
  seriffont-cjk: fonts.serif-font-cjk, 
  sansfont: fonts.sans-font, 
  sansfont-cjk: fonts.sans-font-cjk,
  margin-size: (top: 25mm, bottom: 27mm, left: 20mm, right: 20mm),
  columns: settings.columns,
  fig-separator: settings.fig-tab-separator,
  body) = {
    // メタデータの設定
    let date

    if meta.date == "auto" {
      date = datetime.today()
      //date = date.display("[year]年[month repr:numerical padding:none]月[day padding:none]日")
    } else {
      let date_lst = meta.date.split("-")
      date = datetime(
        year: int(date_lst.at(0)),
        month: int(date_lst.at(1)),
        day: int(date_lst.at(2))
      )
    }

    set document(
      title: meta.title,
      author: meta.author,
      date: date,
      keywords: meta.keywords
    )

    // ページ全体の設定
    set page(numbering: "1", columns: columns, margin: margin-size)
    set footnote(numbering: "1 ")
    
    // 本文の設定
    set text(font: (seriffont, seriffont-cjk), lang: "ja",size: 10pt)
    set par(first-line-indent: (amount: 1em, all: true), leading: 1.0em, justify: true)

    set list(indent: 1.0em, body-indent: 0.8em, marker: ([\u{2022}], [-], [\u{002A}], [・]))
    // 見出しの設定
    set heading(numbering: "1.", bookmarked: true)
    show heading: it => {
      set text(font: (sansfont, sansfont-cjk), lang: "ja", weight: "medium")
      set block(spacing: 1.7em)
      it
    }
    show heading.where(level: 1): set text(size: 14.4pt)
    show heading.where(level: 2): set text(size: 12pt)

    // 図表の設定
    show figure.where(kind: table): set figure(placement: none, supplement: [表])
    show figure.where(kind: table): set figure.caption(position: top, separator: [#fig-separator])

    show figure.where(kind: image): set figure(placement: none, supplement: [図])
    show figure.where(kind: image): set figure.caption(position: bottom, separator: [#fig-separator])

    show figure.where(kind: "list"): set figure(placement: none, supplement: [リスト])
    show figure.where(kind: "list"): set figure.caption(position: top, separator: [#fig-separator])

    
    body
}

// Texのtitlepage環境に相当する関数
#let titlePage(
  content, 
  margin-size: (top: 27mm, bottom: 25mm, left: 20mm, right: 20mm),
  sansfont: fonts.sans-font,
  sansfont-cjk: fonts.sans-font-cjk
  ) = {
    set page(numbering: none, margin: margin-size, columns: 1)
    set text(font: (sansfont, sansfont-cjk), lang: "ja")
    content
    pagebreak()
    counter(page).update(1)
}

// Texのmaketitleに対応する関数
// #let makeTitle(
//   title: "", 
//   authors: "", 
//   keywords: "",
//   date: datetime.today().display("[year]年[month repr:numerical padding:none]月[day padding:none]日"),
//   abstract: []
// ) = {
//   set align(center)
//   v(2em)
//   text(1.7em, title)
//   v(1.5em)
// }

#let includePDF(
  file, 
  margin-size: (top: 0mm, bottom: 0mm, left: 0mm, right: 0mm)
) = {
  set page(numbering: none, margin: margin-size, columns: 1)
  image(file, format: "pdf")
  pagebreak()
  counter(page).update(1)
}

// 手軽なまとめプリントを作りたいとき用の関数
#let printTitle(
  title: "",
  title-font-ja: fonts.serif-font-cjk,
  title-font-en: fonts.serif-font,
  abstract: [],
  name-bar: false
) = {
  set par()
  align(left)[
    #text(size: 20.74pt, font: (title-font-en, title-font-ja))[#title　　]
    #linebreak()
  ]
  abstract
  if name-bar == true {
    align(right)[
      #underline()[\u{3000}]
      年
      #underline()[\u{3000}\u{3000}]
      組
      #underline()[\u{3000}\u{3000}]
      番
      #let c = 0
      #while c < 10 {
        underline()[\u{3000}]
        c = c + 1
      }
    ] 
  }
  v(5pt)
}

#let strong_ja(content) = {
  text(weight: "bold", lang: "ja", font: (fonts.sans-font, fonts.sans-font-cjk))[#content]
}

#let large(content) = {
  text(size:12pt)[#content]
}

#let LARGE(content) = {
  text(size:17.28pt)[#content]
}

#let Large(content) = {
  text(size:14.4pt)[#content]
}

#let huge(content) = {
  text(size:20.74pt)[#content] 
}

#let Huge(content) = {
  text(size: 24.88pt)[#content]
}