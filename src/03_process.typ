#import "@preview/codelst:2.0.2":*
#import "../config.typ":*
#show "、": "，"
#show "。": "．"


#let includeSrc(
  filepath: "",
  lang: "plaintext",
  caption: none,
  numbers-side: "left",
) = {
  figure(
    sourcefile(read(filepath), lang: lang, numbers-side: numbers-side),
    caption: caption,
    kind: "list",
    placement: none,
  )
}

= 実験と考察
== タスクの待ち状態と待ち状態の解除〔課題1〕

3秒毎に起床待ち状態からタイムアウトし，端末にメッセージを表示するタスクtask1を実装したプログラムがある．これに，2秒毎に起床待ち状態からタイムアウトし，端末にメッセージを表示するタスクtask2を追加し，その内容を考察した．

以下に，実装したソースコード`ex11.cfg`，`ex11.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex11.cfg",
  lang: "c",
  caption: [`ex11.cfg`],
)<code:ex11-cfg>

#includeSrc(
  filepath: "./code/ex11.c",
  lang: "c",
  caption: [`ex11.c`],
)<code:ex11>

#includeSrc(
  filepath: "./rlt/ex11ano.txt",
  lang: "shell",
  caption: [ex11の実行結果],
)<rlt:ex11>

== タスクの優先度〔課題2〕

システム時間を監視し，3秒毎に端末にメッセージを表示するタスク`task1`を実装したプログラムがある．これに，2秒毎に起床待ち状態からタイムアウトし，端末にメッセージを表示するタスク`task2`を追加し，その内容と動作を考察した．

以下に，実装したソースコード`ex21.cfg`，`ex21.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex21.cfg",
  lang: "c",
  caption: [`ex21.cfg`],
)<code:ex21-cfg>

#includeSrc(
  filepath: "./code/ex21.c",
  lang: "c",
  caption: [`ex21.c`],
)<code:ex21>

#includeSrc(
  filepath: "./rlt/ex21.txt",
  lang: "shell",
  caption: [ex21の実行結果],
)<rlt:ex21>

== タスクの優先度〔課題3〕

ex21のプログラムについて，task2をtask2よりも先に実行可能状態にするように変更し，その内容と動作を考察した．

以下に，改良したソースコード`ex22.cfg`，`ex22.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex22.cfg",
  lang: "c",
  caption: [`ex22.cfg`],
)<code:ex22-cfg>

#includeSrc(
  filepath: "./code/ex22.c",
  lang: "c",
  caption: [`ex22.c`],
)<code:ex22>

#includeSrc(
  filepath: "./rlt/ex22.txt",
  lang: "shell",
  caption: [ex22の実行結果],
)<rlt:ex22>

== タスクの優先度〔課題4〕
ex21のプログラムについて，task1とtask2の両方が端末にメッセージを表示するようにタスクの優先度を設定し，その内容と動作を考察した．

以下に，改良したソースコード`ex23.cfg`，`ex23.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex23.cfg",
  lang: "c",
  caption: [`ex23.cfg`],
)<code:ex23-cfg>

#includeSrc(
  filepath: "./code/ex23.c",
  lang: "c",
  caption: [`ex23.c`],
)<code:ex23>

#includeSrc(
  filepath: "./rlt/ex23.txt",
  lang: "shell",
  caption: [ex23の実行結果],
)<rlt:ex23>

== 起床待ちによるタスク間同期〔課題5〕
次に示すプログラムを作成し，その内容と動作を考察した．

1. タスク`task1`は，ポートEを監視し，値が変化したらタスク`task2`の起床待ちを解除する．
2. タスク`task2`は，サービスコール`slp_tsk`により自タスクを起床待ち状態に遷移し，タスク`task1`から起床待ちを解除されるとポートEの値を表示する．

以下に，改良したソースコード`ex31.cfg`，`ex31.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex31.cfg",
  lang: "c",
  caption: [`ex31.cfg`],
)<code:ex31-cfg>

#includeSrc(
  filepath: "./code/ex31.c",
  lang: "c",
  caption: [`ex31.c`],
)<code:ex31>

#includeSrc(
  filepath: "./rlt/ex31.txt",
  lang: "shell",
  caption: [ex31の実行結果],
)<rlt:ex31> 

== 起床待ちによるタスク間同期〔課題6〕
次に示すプログラムを作成し，その内容と動作を考察した．

1. タスク`task1`は，@tab:led-display に示すように，端末からの入力された文字によりLEDの表示データのビットパターンを，@code:led-sample に示す表示制御変数`led`に設定するし，タスク`task2`の起床待ちを解除する．
2. タスク`task2`は，サービスコール`slp_tsk`により自タスクを起床待ち状態に遷移し，タスク`task1`から起床待ちを解除されるとタスク`task1`が設定した表示制御変数`led`の値をLEDが接続されているポートDに出力する．

#figure(
  caption: [表示制御変数の例],
  kind: "list",
  sourcecode()[
    ```c
    #include "ex.h"

    uint8_t led = 0;
    
    void task1 (intptr_t exinf) {
      ...
    }
    ```
  ]
)<code:led-sample>

#figure(
  caption: [LEDの表示],
  table(
    columns: 2,
    align:(center, left),
    table.header(
      table.cell(align: center)[*端末からの入力*], 
      table.cell(align: center)[*LEDの表示*],
    ),
    [`r`または`R`], [赤色LEDをトグルする],
    [`g`または`G`], [緑色LEDをトグルする],
    [`b`または`B`], [青色LEDをトグルする],
    [`y`または`Y`], [黄(橙)色LEDをトグルする],
    [`a`または`A`], [全てのLEDを点灯する],
    [`c`または`C`], [全てのLEDを消灯する],
    [`l`または`L`], [下位2ビットのLEDをトグルする],
    [`u`または`U`], [上位2ビットのLEDをトグルする],
  )
)<tab:led-display>

以下に，作成したソースコード`ex41.cfg`，`ex41.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex41.cfg",
  lang: "c",
  caption: [`ex41.cfg`],
)<code:ex41-cfg>

#includeSrc(
  filepath: "./code/ex41.c",
  lang: "c",
  caption: [`ex41.c`],
)<code:ex41>

#includeSrc(
  filepath: "./rlt/ex41.txt",
  lang: "shell",
  caption: [ex41の実行結果],
)<rlt:ex41> 

== 起床待ちによるタスク間同期〔課題7〕
次に示すプログラムを作成し，その内容と動作を考察した．

1. タスク`task1`は、ポートEを監視し、値が変化したら端末ソフトにメッセージを表示する。次に、DIPスイッチのON/OFFに従って、各色のLEDが点灯・消灯するように表示制御変数`led`を設定してタスク`task2`の起床待ちを解除する。
2. タスク`task2`は、サービスコール`slp_tsk()` により自タスクを起床待ち状態に遷移し、タスク`task1` から起床待ちを解除されると、タスク`task1`が設定した表示制御変数（led）の値をLED が接続されているポートDに出力する。

以下に，作成したソースコード`ex42.cfg`，`ex42.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex42.cfg",
  lang: "c",
  caption: [`ex42.cfg`],
)<code:ex42-cfg>

#includeSrc(
  filepath: "./code/ex42.c",
  lang: "c",
  caption: [`ex42.c`],
)<code:ex42>

#includeSrc(
  filepath: "./rlt/ex42.txt",
  lang: "shell",
  caption: [ex42の実行結果],
)<rlt:ex42>   

== セマフォによるタスク間同期〔課題8〕
プログラム`ex31.c`，`ex41.c`，`ex42.c`の何れかを，セマフォによりタスク間の同期を行うプログラムに変更し，変更した内容を考察した．

以下，作成したソースコード`ex61.cfg`，`ex61.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex61.cfg",
  lang: "c",
  caption: [`ex61.cfg`],
)<code:ex61-cfg>

#includeSrc(
  filepath: "./code/ex61.c",
  lang: "c",
  caption: [`ex61.c`],
)<code:ex61>

#includeSrc(
  filepath: "./rlt/ex61.txt",
  lang: "shell",
  caption: [ex61の実行結果],
)<rlt:ex61>

== データキューによるタスク間同期〔課題9〕
プログラム`ex31.c`，`ex41.c`，`ex42.c`の何れかを，データキューによりタスク間の同期を行うプログラムに変更し，変更した内容を考察した．

以下，作成したソースコード`ex71.cfg`，`ex71.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex71.cfg",
  lang: "c",
  caption: [`ex71.cfg`],
)<code:ex71-cfg>

#includeSrc(
  filepath: "./code/ex71.c",
  lang: "c",
  caption: [`ex71.c`],
)<code:ex71>

#includeSrc(
  filepath: "./rlt/ex71.txt",
  lang: "shell",
  caption: [ex71の実行結果],
)<rlt:ex71>

== イベントフラグによるタスク間同期〔課題10〕

次に示すプログラムを作成し，その内容と動作を考察した．

1. タスク`task1`は，@tab:led-display2 に示すように，端末ソフトから入力された文字によりLEDの表示データをフラグ`FLG1`に設定して、サービスコール`set_flg()` によりタスク`task2`の待ちを解除する。
2. タスク`task2`は，サービスコール`wai_flg()`により自タスクを待ち状態に遷移し，タスク`task1`から待ちを解除されると以下の動作を行う．
  - サービスコール`clr_flg()`によりイベントフラグを消去する．
  - タスク`task1`がフラグ`FLG1`に設定したLEDの表示データに従ってLEDを点灯・消灯する．


#figure(
  caption: [LEDの表示],
  table(
    columns: 2,
    align:(center, left),
    table.header(
      table.cell(align: center)[*端末からの入力*], 
      table.cell(align: center)[*LEDの表示*],
    ),
    [`r`または`R`], [赤色LEDをトグルする],
    [`g`または`G`], [緑色LEDをトグルする],
    [`b`または`B`], [青色LEDをトグルする],
    [`y`または`Y`], [黄(橙)色LEDをトグルする],
    [`a`または`A`], [全てのLEDを点灯する],
    [`c`または`C`], [全てのLEDを消灯する],
    [`l`または`L`], [下位2ビットのLEDをトグルする],
    [`u`または`U`], [上位2ビットのLEDをトグルする],
  )
)<tab:led-display2>

以下，作成したソースコード`ex81.cfg`，`ex81.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex81.cfg",
  lang: "c",
  caption: [`ex81.cfg`],
)<code:ex81-cfg>

#includeSrc(
  filepath: "./code/ex81.c",
  lang: "c",  
  caption: [`ex81.c`],
)<code:ex81>

#includeSrc(
  filepath: "./rlt/ex81.txt",
  lang: "shell",
  caption: [ex81の実行結果],
)<rlt:ex81>

== イベントフラグによるタスク間同期〔課題11〕

次に示すプログラムを作成し，その内容と動作を考察した．

1. タスク`task1`は、ポートEを監視し、DIPスイッチのON/OFFによりLEDの表示データをフラグ`FLG1`に設定して、サービスコール`set_flg()`によりタスク`task2`の待ちを解除する。
2. タスク`task2`は、サービスコール`wai_flg()` により自タスクを待ち状態に遷移し、タスク`task1`から起床待ちを解除されると、以下の動作を行う。

  - サービスコール`clr_flg()`によりイベントフラグを消去する．
  - タスク`task1`がフラグ`FLG1`に設定したLEDの表示データを端末に出力する．
  - タスク`task1`がフラグ`FLG1`に設定したLEDの表示データに従ってLEDを点灯・消灯する．

以下に，作成したソースコード`ex82.cfg`，`ex82.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex82.cfg",
  lang: "c",
  caption: [`ex82.cfg`],
)<code:ex82-cfg>

#includeSrc(
  filepath: "./code/ex82.c",
  lang: "c",  
  caption: [`ex82.c`],
)<code:ex82>

#includeSrc(
  filepath: "./rlt/ex82.txt",
  lang: "shell",
  caption: [ex82の実行結果],
)<rlt:ex82>

== ラウンドロビンスケジューリングによるタスク間同期〔課題12〕

次に示すプログラムを作成し，その内容と動作を考察した．

1. 3つのタスク`task1`から`task3`をラウンドロビンスケジューリングにて動作させるタスク`task_rr`を実装する．
2. クオンタムの設定は`main_task`にて行うこととする．
3. 到着順は，`task1`から順であることとしてよい．
4. プリエンプションが起こるときは，必ず`task_rr`が次に実行するタスクを決定する．
5. `task1`から`task3`は，番号に対応するLEDの点灯と消灯を一定周期で入れ替えている．
6. `task1`から`task3`は，自分から起床待ち状態になることはない．

以下，作成したソースコード`ex201.cfg`，`ex201.c`と，その実行結果を示す．

#includeSrc(
  filepath: "./code/ex201.cfg",
  lang: "c",
  caption: [`ex201.cfg`],
)<code:ex201-cfg>

#includeSrc(
  filepath: "./code/ex201.c",
  lang: "c",  
  caption: [`ex201.c`],
)<code:ex201>

#includeSrc(
  filepath: "./rlt/ex201.txt",
  lang: "shell",
  caption: [ex201の実行結果],
)<rlt:ex201>