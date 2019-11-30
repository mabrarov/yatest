if (Test-Path env:MINGW_HOME) {
  $env:PATH = "${env:MINGW_HOME}\bin;${env:PATH}"
}
