
vcpkgをbavil-coreに適応させる為の手段
適応させたいバージョンのコミット or タグのtar.gzをダウンロードしてハッシュ値をportfile.cmakeに記述する必要があります。

# ダウンロード先

サブミットのハッシュから直接DLする為のURL　　

https://github.com/laycnc/bavil-core/archive/${コミットのハッシュ値}.tar.gz

例
```
https://github.com/laycnc/bavil-core/archive/f3b3658cb512f52b80c64fe066ffde01ac45d3ed.tar.gz
```


タグ名から直接DLする為のURL　　

https://github.com/laycnc/bavil-core/archive/refs/tags/v0.08.tar.gz


# ハッシュ値の確認方法

```bat
certutil -hashfile "C:\Users\getsi\Downloads\bavil-core-0.08.tar.gz" SHA512
```

上のコマンドを使うことでハッシュ値を求める事が出来ます。

# portfile.cmakeへの適応

```cmake
vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO laycnc/bavil-core
    REF v0.08 # タグ名 or コミットのハッシュ値に書き換える
    SHA512 4bd8fd18dd408cea06c1797a43f6cfc064f2af3e114455abf07b7fce9bb2038027cada04e6234c88cdfea9099dc3468e305b32ed1e3d1f49c861560bde53cd79 # ここにハッシュ値の書き換えをする
    HEAD_REF main
    PATCHES 
    fix_cmake_install.patch
)```
