= はじめに

ある日、イチゴメロンパンを売っている会社で働くもふもふちゃんは、上司からいきなりこんなことを言われました。

//lead{
「もふもふちゃん、最近イチゴメロンパンの売れ行きが悪いんだ。ちょっと通販用のWebサイトにどのくらいの人がアクセスしているか
調べてくれないかな。日付ごとのグラフとかあると嬉しいなあ。」
//}

//lead{
「あ、そういえばアクセス元もわかるといいよね。将来は海外展開もしたいしね！」
//}

イチゴメロンパンの通販サイトはWebサーバのApache上に構築されているため、Apacheログを解析すればユーザのアクセス数は調べることができそうです。

//lead{
「ええー、このログ全部調べるの…」
//}


Apacheへのアクセス数を数えるためにはリクエストがGETのものだけ数える必要があります。
悪いことに、Webサーバとして利用されているマシンは他の機器とも通信しているようです。人がアクセスした履歴を追いかけるためには
使用している機器のIPアドレスを全て調べ、当てはまるログは解析対象から除外しなければなりません。なかなか骨が折れる作業です。

…数日後、なんとか1週間分のアクセス数とアクセス元を出すことができました。ログの読みすぎで頭はくらくら、目はチカチカします。
そんなもふもふちゃんは解析結果を上司に提出しました。OKをもらえたので立ち去ろうとしたとき、今度はこんな頼まれごとをされてしまいました。

//lead{
「もふもふちゃん、そーいえば最近はTwitterの拡散力は大きいみたいだね。うちのTwitter広報はちゃんと仕事したのか知りたいなあ」
//}

//lead{
「そんなー！Twitterの履歴を追いかけるのは結構大変だよ！もう徹夜したくないよー！」
//}

もふもふちゃんはすっかり困り果ててしまいました。

…ここまで行かないにしろ、最近ではあるサービスの売り上げを伸ばすためであったり、自分の作った作品を宣伝するためには
インターネット上に溢れる情報や、自前のWebサイトへのアクセス履歴を分析する場面が多くなっています。理由としては
アクセスしてくるユーザーに対してダイレクトなマーケティング戦略を取るためであったり、人気の推移を研究することで
より買ってもらえる商品を生み出すためであったりと様々です。

…それができるんです。そう、Elastic Stackであれば！
Elastic StackはオランダのElastic社が提供しているBIツールです。「BIツール」とは、企業や世の中にある色々な情報を集めて分析することを
支援するツールです。このElastic Stackですが、基本はOSSとして提供されており、コードはGithub上で管理されています。
日本でも少しずつ使われる場面が増えてきているようですが、まだまだ知見が少ないというのが現状です。

#@# 44行目のElastic StackをBIツールと称していますが、BIを担っているのはKibanaなので、Stack自体をBIと言ってしまってよいのか？

ただ！このElastic Stackを使えば、情報更新はほぼリアルタイムにすることが可能ですし、
何よりいちいち生ログを閲覧する必要がありません。なんだかとても便利そうです。

//lead{
「ちょっとこのElastic Stackってやつ、自分の環境に入れてみようかな」
//}

みなさんも、もふもふちゃんと一緒に快適なログ解析を始めてみませんか？今までデバックするときくらいにしか使われていなかった
ゴミ同然のログを、ログ解析の力で宝の山に変えることができるかもしれません。

== おことわり
この本で取り扱っている各ツールのバージョンはElasticsearch、Logstash、Kibana共に「5.2」を使用しています。
Elastic Stackはバージョンアップがかなり早いツールです。バージョンによって挙動がかなり違うため、別バージョンを使用した場合と
コンフィグの書き方や操作方法が異なる場合があります。あらかじめご了承ください。

この本はログの分析方法をメインに扱う本です。そのため検索エンジンとしての
Elasticsearchのスキーマ設計など、性能チューニング系のトピックは取り上げません。

筆者のPC環境は@<tt>{macOS Serria（Ver：10.12.2）}です。また、この本ではbrewを用いたElastic Stackのインストールは行いません。

筆者のお財布事情により、本文はモノクロ印刷です。この本ではKibanaの画面キャプチャが複数回出てきますが
モノクロなことをお許しください。本当はカラフルな画面なので、公式サイトや画像検索などでKibana5を参照してみていただけると
テンションが上がると思います。

この本の情報はElastic社の公式ドキュメントを元に作成していますが、
本の情報を用いた開発・制作・運用に対して発生した全ての結果に対して責任は負いません。
必ずご自身の環境でよく検証してから導入をお願いします。

Elastic社の公式URL
@<href>{https://www.elastic.co/guide/index.html}
