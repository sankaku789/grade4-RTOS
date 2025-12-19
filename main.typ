#import "config.typ":*
#import "@preview/codelst:2.0.2":*
#import "@preview/zebraw:0.5.5":*

//#include "title.typ" //学校指定の表紙の場合は，ここをコメントアウトして別途マージしてください。



#show: setup.with()

= 実験の目的

近年，自動車や産業機械，医療機器など様々な分野でリアルタイムOS(RTOS)が採用されている．RTOSは一般的なOSと異なり，タスクの応答時間を保証することが求められるため，タスクのスケージューリングや優先度の設定を適切に行う必要がある．本実験では，RTOSの基本的な仕組みを理解し，演習を通じてタスクのスケジューリングや同期制御を学ぶことを目的とする．

#include "src/01_theory.typ"

#include "src/02_device.typ"

#include "src/03_process.typ"

= まとめ

= 感想

#bibliography("hayagriva.yaml", style: "sist02", full: true)

