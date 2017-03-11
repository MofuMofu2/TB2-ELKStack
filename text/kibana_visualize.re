= グラフの作成

//lead{
　「ログの詳細を検索で出せるのはわかったけど、Googleの画像とかで出てくるのは
もっとかっこいいグラフだけどな？」
//}

　確かにそうですね。今まで使っていたのはログを見る画面なので
Kibanaの紹介で出てくるようなものとは別の画面となります。

　なので、次はグラフを自分で作成してみましょう。
Visualizeタブからグラフを作成します。上から2番目の@<b>{Visualize}ボタンをクリックしましょう。

//image[kibana_chooseVisualize][Visualize画面の選択]{
  キャプチャを貼る
//}

== グラフの選択

#@# キャプチャを入れる

　クリックすると、グラフの種類を選択する画面が出てきます。
選択できるグラフは決まっています。自分で新しい種類のグラフを作ることは今の所できません。
ただしElastic社の公式アナウンスでは、今後PowerPointのようなプレゼンテーションを
Kibana上で作成することができるようになるようです。時期は未定とのことですが、
リリースされればリアルタイムデータを利用しながらプレゼンテーションすることができるようになりそうです。

　まずは、利用できるグラフの一覧を提示します。
//table[kibana_kindOfChart][Kibanaで作成できるグラフの種類]{
グラフ名  概要
----------
Area chart  塗りつぶし型の折れ線グラフ
Data table  表
Heartmap chart  心電図のようにデータの間隔を表示するグラフ
Line chart  折れ線グラフ
Markdown widget Markdown形式で好きに文字を書ける
Pie chart 円グラフ
Tag cloud キーワードを並べることができる
Tile map  位置情報を世界地図にプロットする
Timeseries  時間間隔を表示
Vertical bar chart  棒グラフ
//}


=== Area chart
　データ件数の数だけ塗りつぶして表示されます。SFの映画とかによく出てきそうなグラフですね。

#@#//image[kibana_areaChart][Area chart]{
#@#  キャプチャを貼る
#@#//}

=== Data table
　fieldの中にあるカラムが何件あるか、数を表示することができます。
イメージとしては簡易型のExcelが近いです。
データはCSV形式でダウンロードすることができます。ただし、文字コードはUTF-8なので
Excelで開くと文字化けします。

#@#//image[kibana_dataTable][Data table]{
#@#  キャプチャを貼る
#@#//}

=== Heartmap chart

#@#//image[kibana_heartmapChart][Heartmap chart]{
#@#  キャプチャを貼る
#@#//}

=== Line chart
　データの数に応じて点がプロットされ、それを線でつないだグラフです。
データが存在している期間がばらけていない場合、点しか表示されないのでグラフとしては
見づらいときもたまにあります。

#@#//image[kibana_lineChart][Line chart]{
#@#  キャプチャを貼る
#@#//}

=== Markdown widget
　Markdownを表示することができます。
URLのリンクを記載したり、グラフの閲覧方法をメモ書きで残すことが可能です。

#@#//image[kibana_markdownWidget][Markdown widget]{
#@#  キャプチャを貼る
#@#//}

=== Pie chart
　データの内訳に応じて円が分かれていきます。円を分ける条件を指定しないと
データの総件数が表示されるだけなので、パイを分割する設定を一緒に入れましょう。
工夫次第でドーナツ型のグラフを作ることができます。

#@#//image[kibana_pieChart][Pie chart]{
#@#  キャプチャを貼る
#@#//}

=== Tag cloud

#@#//image[kibana_tagCloud][Tag cloud]{
#@#  キャプチャを貼る
#@#//}

=== Tile map
　データの送信元情報がログなどに含まれていた場合、その情報がどこから来たのか
世界地図にプロットすることが可能です。
この世界地図の情報ですが、世界地図のマップ情報はElastic社のサーバから取得しているため
インターネット環境がないと何もすることができません。
ちなみにKibana3,4などは世界地図情報の取得元サイトがサービスを終了してしまったため
地図グラフを使うことはできなくなってしまいました…。

#@#//image[kibana_tileMap][Tile map]{
#@#  キャプチャを貼る
#@#//}

=== Timeseries

#@#//image[kibana_timeseries][Timeseries]{
#@#  キャプチャを貼る
#@#//}

=== Vertical bar chart
　データ件数の数だけ棒の長さが長くなる、棒グラフです。
#@#//image[kibana_verticalBarChart][Vertical bar chart]{
#@#  キャプチャを貼る
#@#//}

== グラフの作成を行う

では、今度こそグラフを作成しましょう。
好きなグラフを選択します。今回は@<tt>{Pie chart}を選択しました。

//image[kibana_create_pieChart01][Pie chartを選択する]{
  キャプチャを貼る
//}

　すると、Dashboard画面で保存した検索条件を利用するか質問されます。
検索条件を使い回したい場合は@<tt>{Or,From a Saved Search}から検索条件を選んで選択します。
それ以外の場合は@<tt>{From a New Search, Select Index}を利用します。グラフのデータを作成する
index名を選んでクリックします。indexを特に分けていない場合、@<tt>{logstash-*}を選択します。

//image[kibana_create_pieChart02][index選択画面]{
  キャプチャを貼る
//}

　indexを選択すると、自動で円グラフが作成されます。

//image[kibana_create_pieChart03][グラフを作成した直後]{
  キャプチャを貼る
//}

=== metricsの指定

　グラフ作成直後は円グラフの分割をどのように行うか指定されていないため、データ件数を100%として
ただの円が表示されます。画面左側を操作することで、データの数え方やデータの内訳方法を指定することができます。
まずはデータの数え方を決定しましょう。今回は@<tt>{Pie chart}用の設定を取り上げますが、
基本的にはどのグラフであっても同じような内容を設定することになります。

　画面左上の@<tt>{Slice Size}をクリックします。3種類からデータの数え方を選択することができます。

//table[kibana_sliceSize][Slice Sizeの種類]{
Aggregation  Field  Custom Label
----------
Count  -  XX
Sum number型のfieldのみ選択可  XX
Unique Count  全てのfieldから選択可 XX
//}

　データ件数を数えることができれば良い場合、@<tt>{Count}のままで良いです。
この状態でカーソルを円グラフに当てると、データ件数やfield名が表示されます。

=== bucketsの指定

//lead{
　「いろいろ数字が取れるようになったのは便利だけど、Google画像検索とかで出てくるみたいに
色分けするにはどーしたらいいのー？」
//}

　確かにもふもふちゃんの言う通り、今はただの円があるだけです。情報の内訳を表示する機能はありますが、
今は内訳の表示方法を指定できていません。よってデータ数しか表示されないのです。
早速指定してみましょう。

#@#//image[kibana_create_pieChart04][グラフを作成した直後]{
#@#  キャプチャを貼る
#@#//}

==== Aggregation

　まずは、データの内訳方法を決めます。指定できる内訳方法は次の表を参照してください。

//table[Aggregation][Aggregationの種類]{
名前  データの内容
----------
Date Histogram  カラム2
Histogram
Range
Date Range
IPv4 Range
Terms 指定したfield内のデータごとに円グラフの内訳を作成する
Filters  自分で内訳の条件を決定する
Significant Tearms
//}

　今までの設定で作成したfieldごとにデータを分ける場合、Termsを選択します。
詳細設定欄でfield名が選択できるようになりますので、そちらで好きなfieldを選択します。
今回はfield名@<tt>{lang.keyword（つぶやきの言語名）}を選択します。

#@#//image[kibana_create_pieChart05][グラフを作成した直後]{
  キャプチャを貼る
#@#//}

　これで色ごとに情報の内訳を表示することができるようになりました。
画面右上に色に対応したfield名が表示されます。マウスを当てるとそのfieldのみ強調することが可能です。
グラフにマウスを当てるとfield名とデータ件数と全体に占める件数の割合が表示されます。

==== Order By

　デフォルトではデータ数で数を並べ替えることができますが、他にも数のカウント方法を変更することができます。

//table[OrderByList][Order Byの種類]{
名前  内容  補足
----------
metric:Count  データ数による並び替え オプションなし
Custom Metric データの平均など、自分で選択した数の数え方で並べ替え  Aggregationからデータのカウント方法を選択
Term  field名の数で並び替え オプションなし
//}

====　OrderとSize
　@<tt>{Ascending}を選択するとデータが@<b>{多い}順に@<tt>{Size}で指定した数のfieldの内訳が表示されます。
@<tt>{Descending}を選択するとデータが@<b>{少ない}順に@<tt>{Size}で指定した数のfieldの内訳が表示されます。

　指定した数を超えた場合、グラフの表示からは切り捨てられてしまいます。かといってやたらと大きな数を指定すると
ElasticSearchに負荷がかかり、性能が落ちてしまうのでほどほどにしましょう。

==== Custom Label

==== Add Sub buckets
　1つのデータに対して内訳を表示することはできましたが、2種類以上のデータを同じグラフに表示することも可能です。
@<tt>{Add Sub buckets}欄をクリックすると、先ほど同じ設定画面が表示されます。あとは同じようにデータのカウント方法・
内訳方法を指定するだけです。

=== Options
　@<tt>{Options}をクリックするとグラフの見た目を変更することができます。
グラフの種類によって設定内容が変わりますが、今回は@<tt>{Pie chart}のみ取り上げます。

==== Donut
　文字通り、円グラフをドーナツ型にするか選択します。チェックを入れると円グラフがドーナツ型になります。
参考としてXXを準備しましたので、比較して好きな方を選択すれば良いでしょう。

#@#//image[kibana_donut][右：チェックボックスオン　左：チェックボックスオフ]{

#@#//}

==== Legend Position
　画面右に出ているfield名前と色対応を示す部分を@<b>{Legend}といいます。
このオプションを選択することで、画面のどこに@<tt>{Legend}を表示するか指定できます。
上・下・右・左から選択可能です。

==== Show Tooltip
　グラフにカーソルをあてたとき、データの内訳の詳細を表示するか決定できます。
チェックを入れると詳細を表示しますが、外すとグラフにマウスをあてても何も表示されません。

=== グラフを保存する
　グラフを作成後、保存せずにブラウザを閉じた場合は再度作成し直しとなります。
必要に応じてグラフを保存しましょう。

　まずは一度青の三角ボタンをクリックし、設定をグラフに反映します。

　次に画面右上の@<tt>{Save}をクリックし、グラフ名を入力します。
Saveボタンをクリックすると保存完了となります。操作の流れは検索条件を保存するときと同じです。
保存したグラフを表示するときは、@<tt>{Open}をクリックします。こちらも操作方法は同じです。

　@<tt>{Share}をクリックすると、グラフのURLが表示されます。HTMLにURLリンクを入れたい場合（ブログなど）
@<b>{Embedded iframe}のリンクをコピーします。URLリンクとして共有したい場合、@<b>{Link}の方を選択します。

　これでグラフの作成ができました。次はグラフをいくつか並べてみましょう。
