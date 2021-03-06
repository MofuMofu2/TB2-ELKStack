= 終わりに

頑張ってKibanaのDashboard画面を作ったもふもふちゃん。上司の人にはDashboardリンクと
グラフの参照方法を共有したので面倒な仕事を頼まれることも減りました。

//lead{
「いやーよかったよかった！ほとんどリアルタイムで最新情報を表示できるから
メンテナンスもちょっとでいいし楽ちんだよ！」
//}

それはよかったですね。新しい情報をKibanaで表示したくなった場合、Logstashの取り込み元を
新しく指定すれば良いですよね。サーバのデータ（メモリ使用率とか）などを監視する場合は今回は取り上げなかったBeatsを
利用してデータ収集することもできます。

また、今後もELK Stackは機能拡張を行っていくようで、この春ELK Stack5.3もリリースされるようです。@<fn>{ELK Stack5.3}
さらに、Elasticsearchに対してSQLクエリを投げてデータをReadできるようにすることが発表されています。

//footnote[ELK Stack5.3][この本が出ている頃には既にリリースされているかもしれません…。5.2は2017の2月にリリースされたばかりなのですが。]

今回取り上げたTwitter情報を分析する、という使い方はただの一例です。今手元にあるデータとElastic Stackを
組み合わせればデータ分析の可能性は無限大に広がります。データをどう料理するかはみなさん次第です。

それでは楽しいElastic Stackライフを！
