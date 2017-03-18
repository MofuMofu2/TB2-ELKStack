= Kibanaを使ったデータの閲覧

集めたデータを見る前に、ElasticsearchとKibanaの順にサービスを起動しておきましょう。
無事、サービス起動できたらKibanaにアクセスします。

== KibanaのUI
Kibana画面は大きく分けて、データを分析する画面とグラフを作って表示する画面で構成されています。

=== Discover：データの詳細を閲覧する

Discoverは、Elasticsearchのindex内に保持されている生データを閲覧できる箇所です。
fieldごとに分割されたログの詳細をはもちろん、fieldごとのデータのサマリ情報や
何時頃そのログが出力されたか棒グラフを用いて確認することもできます。

//image[kibana_Discover][Discover画面の例]{
  Discoverの画面キャプチャ
//}

=== Visualize：データを使ってグラフを作成する

取り込まれたログを使って棒グラフや折れ線グラフを作成する場所です。
グラフは保存しておくことができるので、昔作ったログを呼び出して参照することも可能です。
ちなみに、グラフの保存先はElasticsearchの中です。

//image[kibana_Visualize][Visualize画面の例]{
  Visualizeの画面キャプチャ
//}

=== Dashboard:グラフを集めて閲覧する
Visualizeで作成したグラフを一箇所にまとめて参照することができます。
Googleの画像検索で出てくるKibanaの画面は、Dashboardの画面が使われることが多いです。
やはりグラフが集まっていると見栄えも良いですよね。

//image[kibana_Dashboard][Dashboard画面の例]{
  Discoverの画面キャプチャ
//}

=== Timelion：関数を定義してグラフを複数描画する
Timelionでは独自の関数を指定すると、グラフを複数描画することができます。
Visualizeでは1つの画面には1種類のグラフしか描画することはできません。
Timelionでは1つの画面に線グラフと棒グラフを両立させることができます。

後ほどVisualizeの紹介で@<tt>{Tile map}というグラフが出てきますが
そちらのグラフと同じ画面です。
今回はデータ種別がテキストと日付しかないため扱いません。

=== Dev Tools：Elasticsearch用のクエリをテストする
Elasticsearchからデータを取得するためには、curlコマンドでGETをElasticsearchに投げます。
Dev ToolsではElasticsearchに直接クエリを投げることができます。

//image[kibana_DevTools][DevTools画面の例]{
  画面キャプチャ
//}

=== Management：Kibanaの設定画面
Elasticsearchのindex情報が更新されたときや、必要なくなったグラフを削除したいときに使用します。
名前の通り設定画面です。

== Discover画面を使ってみよう
まず始めに、Discover画面を使ってデータ分析を行ってみましょう。

=== indexの紐付け
まず初めに、データを表示できる状態にします。
KibanaはElasticsearchのindexからデータを取得していますが、Elasticsearchは複数indexを持つことができます。
Kibanaで利用するindexを指定してあげないと、どの情報を出せばいいのかわかりません。

なので、Logstashの動作確認時に一度どのindexを使うのか指定したのです。
その後Logstashの設定を変更したことにより、新たにfield部分が追加されてしまいました。
でも、Kibana側は古いindex情報を使っているので、「連携されてきたログは何だか別れているけれど、そんな情報は聞いてないぞ？？」と
なってしまうのです。

そこで、新しいfieldを追加した後は新しいindexの情報を取得しないとエラーになってしまうのです。
これを行わないとKibanaで正しく検索ができません。連携するログ情報が増えた後、必ずindexの紐付けを行いましょう。

では、実際にindexの紐付けをおこないます。まず@<b>{Management}画面から@<b>{Index Patterns}画面を開きます。
次に、紐付けるindexの名前と、indexの情報を見せるための時間軸を選択します。
基本はログの中に時間の情報（@timestamp）を保持しているため、そちらを選択します。
最後に@<b>{Save}を選択します。

//image[Kibana_create_index][indexの選択]{
  キャプチャを貼る
//}

これでindex情報の紐付けは完了です。

=== 生ログをみてみよう

では、実際にログを閲覧してみましょう。まずはDashboardの使い方から解説します。
画面左上の1番上のアイコンを選択し、Dashboard画面を開きましょう。

画面左上では、現在何件のデータが取得されているのか表示されます。
その下にある白い枠の中にデータの検索条件を入力し、Enterキーか虫眼鏡マークをクリックすると
検索を行うことができます。検索条件の具体的な記法は後ほど解説します。

//image[kibana_Dashboard_Search][データ数表示と検索条件記入欄]{
  キャプチャを貼る
//}

デフォルトは直近15分の間でElasticsearch内にあるデータが表示されます。データが
何もない場合、@<tt>{Not found}画面が表示されます。データがある場合は
X軸：時間・Y軸：データ件数の棒グラフと、実際にElasticsearchに取り込みされたデータが表示されます。

//image[kibana_Dashboard_Notfound][Elasticsearchにデータがない場合のDashboard画面]{
  キャプチャを貼る
//}

//image[kibana_Dashboard_Datafound][Elasticsearchにデータがある場合のDashboard画面]{
  キャプチャを貼る
//}

実際の生データの詳細は折りたたまれています。これではせっかく取り込みをしたログを
全部表示することができません。ログの左横にある三角マークをクリックすると、ログの全量が表示されます。

=== ログの傾向をみてみよう
では、今度はログの傾向を閲覧してみましょう。Kibanaの左側にある@<b>{Insurance}を利用します。
この@<tt>{Insurance}は直近500件分のログを分析し、各fieldに入っているデータがどのくらい同じなのか
割合で示すことができます。

//image[kibana_Dashboard_Insurance][Insurance]{
  キャプチャを貼る
//}

例えば、@<img>{kibana_Dashboard_Insurance}の
例えば、図で表示されているfieldではログの傾向が〇〇だと一目でわかります。
各データ横にある虫眼鏡をクリックすると、データに当てはまるログが自動で検索されます。
プラスの虫眼鏡を選択すると「そのデータに一致する条件で検索」、マイナスは「そのデータに一致しない条件で検索」となります。

検索条件を指定すると、Dashboard上部に枠が表示されます。解除したい場合、検索条件内の□をクリックするか
ゴミ箱マークをクリックして検索条件ごと消してしまえば良いです。

虫眼鏡マークを選択することで、プラスとマイナスを切り替えることも可能です。

=== 自分で検索してみよう
ある程度はKibanaの機能を使って取得したい情報を絞ることができますが、
自分で検索条件を指定してデータを絞りたいときもあると思います。
特にグラフを作成する場合、あらかじめ検索条件でデータ量を指定しないと
余計な情報までグラフに表示されてしまいます。

==== 条件に一致するものを取り出す
基本的にはfield名を指定し、その後field内のデータを指定する方法をとります。
例えばfield名「tags」に、「CSV」と記載されている情報に絞って
ログを取得したい場合、検索条件は下記のようになります。

//emlist[kibana_Search_sameWord]{
tags:"CSV"
//}

実際に検索をかけるとこのようになります。

//image[kibana_Dashboard_sameWord][条件一致の検索]{
  キャプチャを貼る
//}

実際に内訳をみると、検索条件通りのログが残っていることがわかります。
field名は完全一致で記載する必要がありますが、実際に指定したい条件には
正規表現を利用することができます。よって「〇〇を含む」のような条件指定は正規表現の書き方を用いることで
実現できます。

==== 条件に一致しないものを取り出す
今度は条件に一致しないものは件数としてカウントされないようにしましょう。
例えばfield名「tags」に、「CSV」と記載されている情報は除外して
ログを取得したい場合、field名の頭に@<b>{-}をつけます。マイナスは半角で記載します。

//emlist[kibana_Search_notSameWord]{
-tags:"CSV"
//}

=== 複数検索条件を指定する
KibanaではGoogle検索のように、検索条件を複数指定することができます。
ただしGoogleとは違い、複数の条件指定は明示的に行う必要があります。

==== AかつBの場合を検索する
この場合、検索条件を@<b>{AND}で繋いで指定します。1つのログにAとBの条件に当てはまるものが対象となります。
例えばfield名@<tt>{tags}のログが@<tt>{CSV}に一致するかつ、field名@<tt>{_index}のログが@<tt>{logstash-2017.03.11}に
一致する情報を取得したい場合、検索条件は下記のようになります。

//emlist[kibana_Search_someSearchPattern]{
tags:CSV AND _index:logstash-2017.03.11
//}

逆にfield名@<tt>{tags}のログが@<tt>{CSV}に一致するかつ、field名@<tt>{_index}のログが@<tt>{logstash-2017.03.11}に
一致しない情報を取得したい場合、検索条件に@<b>{AND}を指定する必要はありません。実際の書き方は
下記のようになります。

//emlist[kibana_Search_someSearchPattern_Not]{
tags:CSV -_index:logstash-2017.03.11
//}

==== AまたはBの場合を検索する
この場合、検索条件を@<b>{OR}で繋いで指定します。AまたはBの条件に当てはまるログ全てが検索対象となります。
例えばfield名@<tt>{tags}のログが@<tt>{CSV}に一致するかつ、field名@<tt>{_index}のログが@<tt>{logstash-2017.03.11}に
一致する情報を取得したい場合、検索条件は下記のようになります。

//emlist[kibana_Search_someSearchPattern]{
tags:CSV OR _index:logstash-2017.03.11
//}

field名@<tt>{tags}のログが@<tt>{CSV}に一致するかつ、field名@<tt>{_index}のログが@<tt>{logstash-2017.03.11}に
一致しない情報を取得したい場合、こちらも検索条件に@<b>{OR}を指定する必要はありません。実際の書き方は
下記のようになります。

//emlist[kibana_Search_someSearchPattern_Not]{
-_index:logstash-2017.03.11 OR tags:CSV
//}

=== 検索期間を変えてみよう
Discover画面の右上を見て下さい。時計マークの隣に@<tt>{"Last 15 minutes"}と記載されています。
つまり、今Kibanaに表示されているログは全て15分前のログのみとなります。

//image[kibana_time][Kibanaで表示しているログの検索期間]{
  キャプチャを貼る
//}

このままだと直近のログしか閲覧することができません。
そこで、@<tt>{"Last 15 minutes"}にマウスを合わせてクリックします。

//image[kibana_timeSelect_Quick01][Quickで時刻を選択]{
  キャプチャを貼る
//}

すると、検索時間が選べることがわかります。試しに「Last 7 days」をクリックしてみましょう。

//image[kibana_timeSelected_Quick02][Quickで時刻を選択後]{
  キャプチャを貼る
//}

検索期間が広がったのがわかるでしょうか。@<b>{Quick}からはこのように、ざっくりとした検索期間を指定することが可能です。
他にも検索期間を指定する方法はいくつかあります。

@<b>{Relative}では、「〇〇分前」というような検索期間の指定ができます。
時間の単位をプルダウンから選択し、遡りたい期間を数字で入力します。Goボタンをクリックすることで
指定した条件で再検索することができます。灰色のボタンをクリックすると、ミリ秒以下を切り捨てることができます。

//image[kibana_timeSelect_Relative][Relativeで時刻を選択]{
  キャプチャを貼る
//}

または@<b>{Absolute}を使うことで、カレンダー機能を使って検索範囲を指定することも可能です。

@<b>{Absolute}をクリックすると、カレンダーが表示されます。検索を始めたい期間と終わりの期間をを数字で入力するか、
カレンダーからクリックして選択します。Goボタンを押すことで検索を開始することが可能です。
「Set to Now」をクリックすると、現在の時間に検索終了期間を合わせることができます。

//image[kibana_timeSelect_Absolute][Absoluteで時刻を選択]{
  キャプチャを貼る
//}

3つの検索期間を指定する方法をまとめると、下記のようになります。

//table[kibana_kindOfSearch][検索期間の指定方法]{
Quick Relative  Absolute
---------------------------
決められた期間から指定  遡る期間を指定 検索期間を具体的に指定

カラム1  カラム2
//}

=== 検索条件を保存しよう

//lead{
「色々検索したけど、これ毎回設定するのはめんどくさいね…。使い回しはできないのかな？」
//}

もふもふちゃんの言う通り、ボタンを使って検索条件を絞るにしろ、自分で検索条件を入力するにしろ
毎回条件指定を行うのは面倒ですね。しかし、Kibanaは検索条件を保存することができます。
画面右上の@<b>{Save}アイコンをクリックすると、名前を入れる欄が出てきます。
<tt>{New Saved Search}に好きな名前を入れて@<tt>{Save}ボタンを押しましょう。

//image[kibana_saveSearchPattern_name][保存名の指定]{
  キャプチャを貼る
//}

保存できました。今度は@<b>{New}ボタンを押して、一旦検索条件を指定していない状態に戻してみます。
その後、先ほど保存した検索条件を再度指定してみましょう。@<b>{Open}ボタンをクリックします。
保存している検索条件が出てくるので、呼び出したい検索条件の名前を選択します。

//image[kibana_saveSearchPattern_find][保存した検索条件の選択]{
  キャプチャを貼る
//}

同じ名前で検索条件の詳細をアップデートしたい場合、
条件を書き変えて検索実行をした後、@<b>{Save}ボタンから同じ検索条件を指定することで上書き保存できます。
