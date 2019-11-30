New-Item -Path "${env:BUILD_HOME}" -ItemType "directory" | out-null
Set-Location -Path "${env:BUILD_HOME}"

$generate_cmd = "cmake"
if (${env:TOOLCHAIN} -eq "mingw") {
  $generate_cmd = "${generate_cmd} -D CMAKE_SH=""CMAKE_SH-NOTFOUND"""
}
switch (${env:RUNTIME_LINKAGE}) {
  "static" {
    $generate_cmd = "${generate_cmd} -D CMAKE_USER_MAKE_RULES_OVERRIDE=""${env:APPVEYOR_BUILD_FOLDER}\cmake\static_c_runtime_overrides.cmake"" -D CMAKE_USER_MAKE_RULES_OVERRIDE_CXX=""${env:APPVEYOR_BUILD_FOLDER}\cmake\static_cxx_runtime_overrides.cmake"""
  }
  default {
    $generate_cmd = "${generate_cmd} -D gtest_force_shared_crt=ON"
  }
}
if (${env:TOOLCHAIN} -eq "mingw") {
  $generate_cmd = "${generate_cmd} -D CMAKE_BUILD_TYPE=""${env:CONFIGURATION}"""
}
$generate_cmd = "${generate_cmd} -G ""${env:CMAKE_GENERATOR}"""
if (${env:CMAKE_GENERATOR_PLATFORM}) {
  $generate_cmd = "${generate_cmd} -A ""${env:CMAKE_GENERATOR_PLATFORM}"""
}
$generate_cmd = "${generate_cmd} ""${env:APPVEYOR_BUILD_FOLDER}"""
Write-Host "CMake project generation command: ${generate_cmd}"

Invoke-Expression "${generate_cmd}"
if (${LastExitCode} -ne 0) {
  throw "Generation of project failed with exit code ${LastExitCode}"
}

$build_cmd = "cmake --build . --config ""${env:CONFIGURATION}"""
if ((${env:TOOLCHAIN} -eq "msvc") -and (${env:MSVC_VERSION} -ne "9.0")) {
  $build_cmd = "${build_cmd} -- /maxcpucount /verbosity:normal /logger:""C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"""
}
Write-Host "CMake project build command: ${build_cmd}"

Invoke-Expression "${build_cmd}"
if (${LastExitCode} -ne 0) {
  throw "Build failed with exit code ${LastExitCode}"
}

Set-Location -Path "${env:APPVEYOR_BUILD_FOLDER}"
