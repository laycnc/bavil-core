# vcpkgのprofile.cmakeを最新のgitのコミットの物を参照するように変える

# gitの最新コミットのハッシュをクリップボードに貼り付け
git rev-parse HEAD | Set-Clipboard
# 変数にコピー
$git_hash = Get-Clipboard

Write-Output "githubからファイルのダウンロードを行います..."

# ダウンロード用のURLを用意
$archive_url = "https://github.com/laycnc/bavil-core/archive/${git_hash}.tar.gz"

# ダウンロード先のファイルパスを用意
$download_path = "C:/Users/getsi/Downloads/bavil-core-${git_hash}.tar.gz"

Write-Output "url=${archive_url}: dl=${download_path}"

# ファイルを保存
Invoke-WebRequest -Uri $archive_url -OutFile $download_path

# ファイルからハッシュ値を求める
$file_hash_result = Get-FileHash $download_path -Algorithm SHA512
$file_hash = $file_hash_result.Hash

$current_dir = Split-Path $MyInvocation.MyCommand.Path

# 書き換え対象のファイルのパスを作成する
$profile_cmake = Join-Path $current_dir "../../external/vcpkg/ports/bavil-core/portfile.cmake"
$profile_cmake = Convert-Path $profile_cmake

Write-Output "${profile_cmake}の書き換えを行います"
Write-Output "REF ${git_hash}"
Write-Output "SHA512 ${file_hash}"

# 参照するコミットとダウンロードしたハッシュ値に書き換える
(Get-Content $profile_cmake) | `
    ForEach-Object { $_ -replace "    REF ..*", "    REF ${git_hash}" } | `
    ForEach-Object { $_ -replace "    SHA512 ..*", "    SHA512 ${file_hash}" } | `
    Set-Content $profile_cmake
