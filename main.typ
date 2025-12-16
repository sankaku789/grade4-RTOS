#import "config.typ":*
#import "@preview/codelst:2.0.2":*
#import "@preview/zebraw:0.5.5":*

//#include "title.typ" //学校指定の表紙の場合は，ここをコメントアウトして別途マージしてください。

#show: setup.with()

= 実験の目的


//#include "src/research.typ"

#include "src/01_theory.typ"

#include "src/02_device.typ"

#include "src/03_process.typ"

#include "src/04_progress.typ"

#include "src/05_result.typ"

#include "src/06_consideration.typ"


= まとめ

#bibliography("hayagriva.yaml", style: "ieee", full: true)

