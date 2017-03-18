= 環境構築

//lead{
「よーし、ELKがどんなものかだいたい理解できたから、インストールしてみよ！
…あれ、なんかインストール方法もいっぱいあるみたい。どれを選べばいいのかなあ？」
//}

あら？もふもふちゃん、今度はインストールで詰まってしまったようです。
公式サイトからダウンロードでzipファイルを落としてくることができるようですが、他のやり方もあるようです。
状況に合っている1番いいやり方を選択したいですよね。一緒にみてみましょう。

== インストールの順番
インストールの前に、どのツールからインストールするかを決めておきましょう。ELKのデータの流れを考えると、
Elasticsearch→Logstash→Kibanaの順にインストールすることをお勧めします。
理由は @<img>{data}にあるように、Logstashで取りこんだデータをElasticsearchに連携するため
先にデータの連携先をセットアップしておかないと正しく動作確認ができない可能性があるためです。

//image[data][データ連携の流れ]{
  配置場所
  /Users/mallow/review/text/text/images/data.png
//}

また、Kibanaは起動前にElasticsearchのURLを指定する必要があるため、Elasticsearchがセットアップされていないと
そもそも動作しません。今回は各ツールごとに完結できる動作確認方法を取りますが、万が一に備えるという意味では
図X.Xのようにデータの連携先→連携元→データ閲覧ツールという流れでセットアップした方が良いでしょう。

//image[install][セットアップの順番]{
  配置場所
  /Users/mallow/review/text/text/images/data.png
//}

== 事前準備

Elasticsearch、Logstashの起動にはJava（バージョン8以上）が必要です。
必要に応じてインストールしましょう。

//cmd{
$ java -version
java version "1.8.0_45"
Java(TM) SE Runtime Environment (build 1.8.0_45-b14)
Java HotSpot(TM) 64-Bit Server VM (build 25.45-b02, mixed mode)
//}

== Elasticsearchのインストール
先にも述べましたが、インストール方法は複数準備されています。導入の目的とご自身の環境に合わせて
ベストなものを選択すると良いでしょう。

=== とにかく使ってみたい場合（Linux）：zipファイル

「とにかくどんなものか試してみたい！」そんな方はzipファイルを公式サイトからダウンロードしてきましょう。
インストール方法も適当なフォルダにzipファイルを解凍するだけなので導入は簡単に終わります。
ただし、サービス起動用コマンドは付属しないため、長期的な運用を考えている場合には向かないインストール方法です。

=== ちゃんと運用もしたい場合（RedHat系Linux）：rpmパッケージ
公式にElasticから提供されているrpmパッケージを利用した場合、サービス起動用コマンドが自動的に設定されます。
また、各種設定ファイルやディレクトリ構造はLinuxのディレクトリ形式に合わせて構築されます。
運用を検討している場合は、初めからこちらのやり方を取っておけば環境の再構築を防ぐことができます。

=== ちゃんと運用もしたい場合（Debian系Linux）：debパッケージ
こちらもrpmパッケージを利用する方法と同様です。違いはUbuntu系のLinux用パッケージを使うか、
RedHat、OpenSuSE系のLinux用パッケージを使うかだけです。

=== とにかく使ってみたい場合かつ、Docker実行環境がある場合：Dockerコンテナ
Elastic StackをDocker社が利用していることもあってか、公式にElasticからDockerイメージが提供されています。
手っ取り早く試してみたい場合、かつDockerコンテナの実行環境がある場合は素直にコンテナを利用した方が良いでしょう。
ただし、インストール方式の2.3に移行を考えている場合、構成がかなり変わるので初めからパッケージ利用での環境構築方法を選択した方が良さそうです。

また、Elasticsearchは物理的にも、Javaのヒープメモリもかなり消費するツールです。
Dockerコンテナ上ではあまり性能が出ないため、大量のデータを流す予定がある場合はコンテナ利用を避けた方が良いです。

=== Puppet、Chef、Ansibleの実行環境がある場合：Githubのレシピを利用
公式にElasticから各ツールのレシピが共有されています。Githubにアップロードされているため
そちらを用いて環境を構築することも可能です。

=== Windows/Mac上に構築する場合：zipファイル
Windowsの場合、インストール方法はzipファイル一択となります。Macはbrewコマンドを用いることで
インストールすることもできますが、Elastic公式ではサポートされていないようなので、
今回はインストール方法から対象外としています。

他の方が検証されているブログなどを見る限り、brewコマンドでインストールした場合はtar.gzパッケージを解凍して
インストールしているようです。公式の最新ファイルをダウンロードしてインストールするのと変わらないため、
好みで選択すると良いでしょう。

== zipファイルを用いたインストール（Elasticsearch）

今回は6のzipファイルを用いたインストール方法を取りたいと思います。
zipファイルを用いたインストールの場合、OSが違っていても基本的な手順は同じです。


=== 公式サイトからzipファイルをダウンロード

Elasticの公式サイトにアクセスし、zipファイルをダウンロードします。

@<href>{https://www.elastic.co/jp/downloads/elasticsearch}

//image[Elasticsearch_download][Elasticsearchのダウンロード]{
/Users/mallow/review/text/text/images/Elasticsearch_download.png
//}

=== 作業用ディレクトリを作成（好みで良いです）

今回は検証用の環境構築なので、アンインストールを簡単にするために作業用ディレクトリを作成します。

//cmd{
$ mkdir ELK_Stack
//}

=== zipファイルの解凍

ディレクトリ内にダウンロードしたzipファイルを解凍します。

//cmd{
# 必要であれば
$ unzip Elasticsearch-5.2.2
//}

=== メモリ使用率の変更（必要であれば）

ElasticsearchはJavaで動くアプリなのですが、最大ヒープサイズ（Xms）は物理メモリの50%以下である必要があります。
メモリが50%以上を超えてしまう場合、Elasticsearchプロセスが立ち上がりません。
ヒープサイズは次の設定ファイルで設定します。

//emlist[ヒープサイズの設定ファイル]{
/elasticsearch-5.2.2/config/jvm.options
//}

@<code>{-Xms}は初期ヒープサイズの設定を行い、@<code>{-Xmx}では最大ヒープサイズの設定を行います。
サーバの物理メモリが4GBであれば、2GBで設定しておくと良いでしょう。

//emlist[ヒープサイズの設定]{
$ sudo vim jvm.options

 19 # Xms represents the initial size of total heap space
 20 # Xmx represents the maximum size of total heap space
 21
 22 -Xms2g
 23 -Xmx2g
//}

=== Elasticsearchの起動

@<tt>{/bin}ディレクトリ下にある@<tt>{Elasticsearch}スクリプトを実行し、サービスを起動します。
OSがWindowsの場合、@<tt>{Elasticsearch.bat}を実行します。

起動コマンドは次の通りです。@<tt>{-d}オプションを利用すると、バックグラウンドで実行できます。

//emlist[Elasticsearchの起動コマンド]{
bin/elasticsearch
# -dオプションでバックグラウンド実行
bin/elasticsearch -d
//}

//cmd{
$ Elasticsearch-5.2.2 mofumofu$ bin/elasticsearch
//}

=== 動作確認

Elasticsearchへクエリを投げ、返り値があるか確認します。
返り値が帰ってくれば、正常にインストールできています。

//cmd{
# Elasticsearchの稼動確認
$ curl http://localhost:9200/
{
  "name" : "asgUjsK",
  "cluster_name" : "Elasticsearch",
  "cluster_uuid" : "aK9PZbz4SCSbg3Bi_j_R_g",
  "version" : {
    "number" : "5.2.2",
    "build_hash" : "f9d9b74",
    "build_date" : "2017-02-24T17:26:45.835Z",
    "build_snapshot" : false,
    "lucene_version" : "6.4.1"
  },
  "tagline" : "You Know, for Search"
}
//}

もしくはGoogle Chrome上でURLにアクセスし、同じような返り値があればOKです。

//image[localhost_9200][Elasticsearchの起動確認]{
/Users/mallow/review/text/text/images/localhost_9200.png
//}

== Logstashのインストール

LogstashもElasticsearchと同様、インストール方式を選択することが可能です。
ただ、ツールごとにインストール方式を分けるやり方は、ディレクトリ構造が異なってしまうため避けた方が良いです。

==={logstash-zip} とにかく使ってみたい場合（Linux）：zipファイル

こちらもElasticsearchと同様、zipファイルを展開するだけでインストールが終了します。
サービス起動用コマンドは付属しません。

==={logstash-rpm}  ちゃんと運用もしたい場合（rpmパッケージを利用するLinux）：rpmパッケージ
こちらもサービス起動用コマンドの存在や、ディレクトリ構成が自動で割り当てられる点なども
Elasticsearchと同様です。

==={logstash-deb} ちゃんと運用もしたい場合（debパッケージを利用するLinux）：debパッケージ
こちらもElasticsearchと同様です。

==={logstash-docker} とにかく使ってみたい場合かつ、Docker実行環境がある場合：Dockerコンテナ
Elasticsearchと同様、Elastic社からDockerコンテナが提供されています。
ただし、Elasticsearchとは別のコンテナのため、同時にコンテナを複数起動する必要があります。

LogstashはRubyで作成されていますが、起動にJavaを必要とします。
こちらもヒープメモリもかなり消費するツールなので注意が必要です。

==={logstash-com} Puppet、Chef、Ansibleの実行環境がある場合：Githubのレシピを利用
公式にElasticから各ツールのレシピが提供されているので、Githubからクローンして利用することも可能です。

==={logstash-win} Windows/Mac上に構築する場合：zipファイル
Windowsの場合、インストール方法はzipファイル一択となります。Macはbrewコマンドを用いることで
インストールすることもできますが、Elastic公式ではサポートされていないようなので、
今回はインストール方法から除外しています。

== zipファイルを用いたインストール(Logstash)

Elasticsearchのインストール方法に合わせるため、6のzipファイルを用いたインストール方法を取ります。
こちらも、OSごとに手順に差はありません。

==={logstash-dl} 公式サイトからzipファイルをダウンロード

Elasticの公式サイトにアクセスし、zipファイルをダウンロードします。

@<href>{https://www.elastic.co/jp/downloads/logstash}

//image[logstash_download][Logstashのダウンロード]{
  /Users/mallow/review/text/text/images/logstash_download.png
//}

==={logstash-unzip} zipファイルの解凍

Elasticsearchをインストールする際に作成したディレクトリに、ダウンロードしたzipファイルを解凍します@<fn>{install_dir}。

//footnote[install_dir][今回のディレクトリ構成はあくまでも一例です。個人のお好みで設定するのが1番です。]

//cmd{
# 必要であれば
unzip logstash-5.2.2
//}

==={logstash-conf} 動作確認用のlogstash.conf作成

この後の章で詳しく述べますが、Logstashはlogstash.confを読み込むことで
ファイルの取り込み元などを指定します。まずは動作確認用に次のコードをconfファイルへ記述します。

//cmd{
# zipファイルを展開して作成されたディレクトリ内でlogstash.confを作成
logstash-5.2.2 mofumofu$ touch logstash.conf
//}

次に、logstash.confを編集します。
//cmd{
# logstash.confの編集
logstash-5.2.2 mofumofu$ vi logstash.conf

# 下記の通り編集
-----------------------------------------------------
# 標準入力を受け付ける
input {
  stdin { }
}
# 標準出力を行う
output {
  stdout { codec => rubydebug }
}
//}

==={logstash-test} 動作確認

@<tt>{/bin}下にある@<tt>{logstash}スクリプトから、Logstashを起動します。
OSがWindowsの場合、同階層に@<tt>{logstash.bat}が配置されているのでそちらを起動します。

Logstashの起動をコマンドで行う場合、次の通りに実行します。
@<code>{-f}オプションで@<tt>{logstash.conf}の名前を指定します。

//emlist[Logstashの起動]{
$ /bin/logstash -f logstash.conf
//}

@<tt>{logstash.conf}にタイプミスがない場合、<@<tt>{"Logstash startup completed"}と出力されます。
コマンドプロンプトに好きな文字列を打ち込んでみましょう。
文字列がそのまま返り値として出力された場合、正しくセットアップできています。

//cmd{
logstash-5.2.2 mofumofu$ bin/logstash -f logstash.conf

# 標準入力で"hello world"を入力
hello world
{
    "@timestamp" => 2017-03-05T07:22:40.899Z,
      "@version" => "1",
          "host" => "mofumofu-no-MacBook-Pro.local",
       "message" => "hello world"
}
//}

== Kibanaのインストール

Kibanaも他ツールと同様、インストール方法が複数準備されています。
種類はElasticsearch・Logstashと変わらないため、そちらの章を参照してください。

==={kibana-install} zipファイルを用いたインストール

ElasticsearchとLogstashのインストール方法に合わせるため、zipファイルを用いたインストール方法を選択しました。
こちらも、OSごとに手順に差はありません。

==={kibana-zip} 公式サイトからzipファイルをダウンロード

Elasticの公式サイトにアクセスし、zipファイルをダウンロードします。
OSの種類によってzipファイルが異なるため、注意が必要です。

@<href>{https://www.elastic.co/jp/downloads/kibana}

//image[kibana_download][Kibanaのダウンロード]{
/Usersmofumofu/review/text/text/images/kibana_download.png
//}

==={kibana-unzip} zipファイルの解凍

Elasticsearchをインストールする際に作成したディレクトリに、ダウンロードしたzipファイルを解凍します。

//cmd{
# 必要であれば
unzip kibana-5.2.2-darwin-x86_64.tar.gz
//}

==={kibana-yml} kibana.ymlの編集

前にも述べた通り、KibanaはElasticsearchからデータを取得するためElasticsearchのURLを指定する必要があります。
kibana.yml内にURLを指定する箇所があるのでそちらを記述しましょう。kibana.ymlのパスは
@<code>{/フォルダ名/kibana-5.2.2-linux-x86_64/config/kibana.yml}です@<fn>{kibana.yml}。

KibanaはElasticsearchと連動して動くアプリケーションなので、
@<tt>{kibana.yml}を編集するときはElasticsearchプロセスを停止しておいた方が良いでしょう。

//footnote[kibana.yml][zipファイルを解凍してインストールした場合はこちらのパスになりますが、パッケージインストールの場合ディレクトリ階層が異なります。]

//cmd{
# 21行目の下にURLを追記
--------------------------------------------------------------------
20 # The URL of the Elasticsearch instance to use for all your queries.
21 #Elasticsearch.url: "http://localhost:9200"
   Elasticsearch.url: "http://localhost:9200"
--------------------------------------------------------------------
//}

==={kibana-test} 動作確認

/binフォルダ下にあるkibanaスクリプトから起動します。起動前にElasticsearchを起動しておいてください。（Windowsはkibana.batから起動します。）

//cmd{
kibana-5.2.2-darwin-x86_64 mofumofu$ bin/kibana
//}

起動後、ブラウザに@<href>{http://localhost:5601}と入力します。図X.Xのような画面が見えていればインストールは完了です。

//image[kibana_setup][Kibanaの画面]{
/Usersmofumofu/review/text/text/images/kibana_setup.png
//}
