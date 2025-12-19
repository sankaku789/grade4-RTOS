#import "@preview/codelst:2.0.2": *
#show "、": "，"
#show "。": "．"

#let includeSrc(
  filepath: "",
  lang: "plaintext",
  caption: none,
  numbers-side: "left",
) = {
  figure(
    sourcefile(read(filepath), lang: lang, numbers-side: numbers-side)[
      code
    ],
    caption: caption,
    kind: "list",
  )
}

= 実験と考察
== 課題1について
== 課題2について
== 課題3について
== 課題4について
== 課題5について
== 課題6について
== 課題7について
== 課題8について
== 課題9について
== 課題10について
== 課題11について
//== 課題12