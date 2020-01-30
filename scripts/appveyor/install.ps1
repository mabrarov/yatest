$env:OS_VERSION = (Get-WmiObject win32_operatingsystem).version

$vswhere_home = "${env:DEPENDENCIES_FOLDER}\vswhere-${env:VSWHERE_VERSION}"
$vswhere_executable = "${vswhere_home}\${env:VSWHERE_DIST_NAME}"
if (!(Test-Path -Path "${vswhere_executable}")) {
  Write-Host "Visual Studio Locator ${env:VSWHERE_VERSION} not found at ${vswhere_home}"
  $vswhere_archive_file = "${env:DOWNLOADS_FOLDER}\${env:VSWHERE_DIST_NAME}"
  $vswhere_download_url = "${env:VSWHERE_URL}/${env:VSWHERE_VERSION}/${env:VSWHERE_DIST_NAME}"
  if (!(Test-Path -Path "${vswhere_archive_file}")) {
    Write-Host "Downloading Visual Studio Locator ${env:VSWHERE_VERSION} from ${vswhere_download_url} to ${vswhere_archive_file}"
    if (!(Test-Path -Path "${env:DOWNLOADS_FOLDER}")) {
      New-Item -Path "${env:DOWNLOADS_FOLDER}" -ItemType "directory" | out-null
    }
    curl.exe `
      --connect-timeout "${env:CURL_CONNECT_TIMEOUT}" `
      --max-time "${env:CURL_MAX_TIME}" `
      --retry "${env:CURL_RETRY}" `
      --retry-delay "${env:CURL_RETRY_DELAY}" `
      --show-error --silent --location `
      --output "${vswhere_archive_file}" `
      "${vswhere_download_url}"
    if (${LastExitCode} -ne 0) {
      throw "Downloading of Visual Studio Locator failed with exit code ${LastExitCode}"
    }
    Write-Host "Downloading of Visual Studio Locator completed successfully"
  }
  if (!(Test-Path -Path "${vswhere_home}")) {
    New-Item -Path "${vswhere_home}" -ItemType "directory" | out-null
  }
  Write-Host "Copying Visual Studio Locator ${env:VSWHERE_VERSION} from ${vswhere_archive_file} to ${vswhere_home}"
  Copy-Item -Path "${vswhere_archive_file}" -Destination "${vswhere_home}" -Force
  Write-Host "Copying of Visual Studio Locator completed successfully"
}

$toolchain_id = ""
switch (${env:TOOLCHAIN}) {
  "msvc" {
    $env:TOOLCHAIN_ID = "${env:TOOLCHAIN}-${env:MSVC_VERSION}"
    $env:WINDOWS_SDK_ENV_BATCH_FILE = ""
    $env:WINDOWS_SDK_ENV_PARAMETERS = ""
    $env:MSVS_HOME = "${env:ProgramFiles(x86)}\Microsoft Visual Studio ${env:MSVC_VERSION}"
    $env:MSVC_VARS_BATCH_FILE = "${env:MSVS_HOME}\VC\vcvarsall.bat"
    $env:MSVS_PATCH_FOLDER = ""
    $env:MSVS_PATCH_BATCH_FILE = ""
    $msvs_install_dir = ""
    switch (${env:MSVC_VERSION}) {
      "14.2" {
        $msvs_install_dir = &"${vswhere_executable}" --% -latest -products Microsoft.VisualStudio.Product.Community -version [16.0,17.0) -requires Microsoft.VisualStudio.Workload.NativeDesktop -property installationPath
      }
      "14.1" {
        $msvs_install_dir = &"${vswhere_executable}" --% -latest -products Microsoft.VisualStudio.Product.Community -version [15.0,16.0) -requires Microsoft.VisualStudio.Workload.NativeDesktop -property installationPath
      }
    }
    switch (${env:PLATFORM}) {
      "x86" {
        switch (${env:MSVC_VERSION}) {
          "14.2" {
            $env:MSVC_VARS_BATCH_FILE = "${msvs_install_dir}\VC\Auxiliary\Build\vcvars32.bat"
            $env:MSVC_VARS_PLATFORM = ""
          }
          "14.1" {
            $env:MSVC_VARS_BATCH_FILE = "${msvs_install_dir}\VC\Auxiliary\Build\vcvars32.bat"
            $env:MSVC_VARS_PLATFORM = ""
          }
          default {
            $env:MSVC_VARS_PLATFORM = "x86"
          }
        }
      }
      "x64" {
        switch (${env:MSVC_VERSION}) {
          "14.2" {
            $env:MSVC_VARS_BATCH_FILE = "${msvs_install_dir}\VC\Auxiliary\Build\vcvars64.bat"
            $env:MSVC_VARS_PLATFORM = ""
          }
          "14.1" {
            $env:MSVC_VARS_BATCH_FILE = "${msvs_install_dir}\VC\Auxiliary\Build\vcvars64.bat"
            $env:MSVC_VARS_PLATFORM = ""
          }
          "14.0" {
            $env:MSVC_VARS_PLATFORM = "amd64"
          }
          "12.0" {
            $env:MSVC_VARS_PLATFORM = "amd64"
          }
          "11.0" {
            $env:MSVC_VARS_PLATFORM = "x86_amd64"
          }
          "10.0" {
            $env:MSVC_VARS_BATCH_FILE = ""
            $env:WINDOWS_SDK_ENV_BATCH_FILE = "${env:ProgramFiles}\Microsoft SDKs\Windows\v7.1\Bin\SetEnv.cmd"
            $env:WINDOWS_SDK_ENV_PARAMETERS = "/x64 /${env:CONFIGURATION}"
          }
          "9.0" {
            Write-Host "Chosen MSVS version (${env:MSVC_VERSION}) and platform (${env:PLATFORM}) require patching"
            $env:MSVS_PATCH_FOLDER = "${env:DEPENDENCIES_FOLDER}\vs2008_patch"
            if (!(Test-Path -Path "${env:MSVS_PATCH_FOLDER}")) {
              $msvs_patch_download_folder = "${env:DOWNLOADS_FOLDER}\condaci"
              $msvs_patch_download_file = "${msvs_patch_download_folder}\vs2008_patch.zip"
              if (!(Test-Path -Path "${msvs_patch_download_file}")) {
                $msvs2008_patch_url = "https://github.com/menpo/condaci.git"
                $msvs2008_patch_revision = "98d76b2089d494433ac2e3abd920123088a95a6d"
                $msvs_patch_download_folder_nix = "${msvs_patch_download_folder}" -replace "\\", "/"
                Write-Host "Downloading MSVS patch from ${msvs2008_patch_url} to ${msvs_patch_download_folder_nix}"
                git clone --quiet "${msvs2008_patch_url}" "${msvs_patch_download_folder_nix}"
                git -C "${msvs_patch_download_folder_nix}" checkout --quiet "${msvs2008_patch_revision}"
                if (${LastExitCode} -ne 0) {
                  throw "Downloading of MSVS patch failed with exit code ${LastExitCode}"
                }
                Write-Host "Downloading of MSVS patch completed successfully"
              }
              Write-Host "Extracting MSVS patch from ${msvs_patch_download_file} to ${env:MSVS_PATCH_FOLDER}"
              New-Item -Path "${env:MSVS_PATCH_FOLDER}" -ItemType "directory" | out-null
              7z.exe x "${msvs_patch_download_file}" -o"${env:MSVS_PATCH_FOLDER}" -aoa -y | out-null
              if (${LastExitCode} -ne 0) {
                throw "Extracting MSVS patch failed with exit code ${LastExitCode}"
              }
              Write-Host "Extracting of MSVS patch completed successfully"
            }
            Write-Host "MSVS patch is located at ${env:MSVS_PATCH_FOLDER}"
            $env:MSVS_PATCH_BATCH_FILE = "${env:MSVS_PATCH_FOLDER}\setup_x64.bat"
            $env:MSVC_VARS_PLATFORM = "x86_amd64"
          }
          default {
            throw "Unsupported ${env:TOOLCHAIN} version: ${env:MSVC_VERSION}"
          }
        }
      }
      default {
        throw "Unsupported platform for ${env:TOOLCHAIN} toolchain: ${env:PLATFORM}"
      }
    }
    $env:ARTIFACT_PATH_SUFFIX = "\${env:CONFIGURATION}\"
  }
  "mingw" {
    $env:TOOLCHAIN_ID = "${env:TOOLCHAIN}-${env:MINGW_VERSION}"
    $mingw_platform_suffix = ""
    $mingw_thread_model_suffix = ""
    switch (${env:PLATFORM}) {
      "x86" {
        $mingw_platform_suffix = "i686-"
        $mingw_exception_suffix = "-dwarf"
      }
      "x64" {
        $mingw_platform_suffix = "x86_64-"
        $mingw_exception_suffix = "-seh"
      }
      default {
        throw "Unsupported platform for ${env:TOOLCHAIN} toolchain: ${env:PLATFORM}"
      }
    }
    $env:MINGW_HOME = "C:\mingw-w64\${mingw_platform_suffix}${env:MINGW_VERSION}-posix${mingw_exception_suffix}-rt_v${env:MINGW_RT_VERSION}-rev${env:MINGW_REVISION}\mingw64"
    $env:ARTIFACT_PATH_SUFFIX = "\"
  }
  default {
    throw "Unsupported toolchain: ${env:TOOLCHAIN}"
  }
}

try {
  $detected_cmake_version = (cmake --version 2> $null `
    | Where-Object {$_ -match 'cmake version ([0-9]+\.[0-9]+\.[0-9]+)'}) `
    -replace "cmake version ([0-9]+\.[0-9]+\.[0-9]+)", '$1'
} catch {
  $detected_cmake_version = ""
}
Write-Host "Detected CMake of ${detected_cmake_version} version"
if (Test-Path env:CMAKE_VERSION) {
  Write-Host "CMake of ${env:CMAKE_VERSION} version is requested"
  if (${env:CMAKE_VERSION} -ne ${detected_cmake_version}) {
    if ([System.Version] "${env:CMAKE_VERSION}" -ge [System.Version] "3.6.0") {
      $cmake_archive_base_name = "cmake-${env:CMAKE_VERSION}-win64-x64"
    } else {
      # CMake x64 binary is not available for CMake version < 3.6.0
      $cmake_archive_base_name = "cmake-${env:CMAKE_VERSION}-win32-x86"
    }
    $cmake_home = "${env:DEPENDENCIES_FOLDER}\${cmake_archive_base_name}"
    if (!(Test-Path -Path "${cmake_home}")) {
      Write-Host "CMake ${env:CMAKE_VERSION} not found at ${cmake_home}"
      $cmake_archive_name = "${cmake_archive_base_name}.zip"
      $cmake_archive_file = "${env:DOWNLOADS_FOLDER}\${cmake_archive_name}"
      $cmake_download_url = "https://github.com/Kitware/CMake/releases/download/v${env:CMAKE_VERSION}/${cmake_archive_name}"
      if (!(Test-Path -Path "${cmake_archive_file}")) {
        Write-Host "Downloading CMake ${env:CMAKE_VERSION} archive from ${cmake_download_url} to ${cmake_archive_file}"
        if (!(Test-Path -Path "${env:DOWNLOADS_FOLDER}")) {
          New-Item -Path "${env:DOWNLOADS_FOLDER}" -ItemType "directory" | out-null
        }
        curl.exe `
          --connect-timeout "${env:CURL_CONNECT_TIMEOUT}" `
          --max-time "${env:CURL_MAX_TIME}" `
          --retry "${env:CURL_RETRY}" `
          --retry-delay "${env:CURL_RETRY_DELAY}" `
          --show-error --silent --location `
          --output "${cmake_archive_file}" `
          "${cmake_download_url}"
        if (${LastExitCode} -ne 0) {
          throw "Downloading of CMake failed with exit code ${LastExitCode}"
        }
        Write-Host "Downloading of CMake completed successfully"
      }
      if (!(Test-Path -Path "${env:DEPENDENCIES_FOLDER}")) {
        New-Item -Path "${env:DEPENDENCIES_FOLDER}" -ItemType "directory" | out-null
      }
      Write-Host "Extracting CMake ${env:CMAKE_VERSION} from ${cmake_archive_file} to ${env:DEPENDENCIES_FOLDER}"
      7z.exe x "${cmake_archive_file}" -o"${env:DEPENDENCIES_FOLDER}" -aoa -y | out-null
      if (${LastExitCode} -ne 0) {
        throw "Extracting CMake failed with exit code ${LastExitCode}"
      }
      Write-Host "Extracting of CMake completed successfully"
    }
    Write-Host "CMake ${env:CMAKE_VERSION} is located at ${cmake_home}"
    $env:PATH = "${cmake_home}\bin;${env:PATH}"
  }
}

switch (${env:CONFIGURATION}) {
  "Debug" {
    $env:CMAKE_BUILD_CONFIG = "DEBUG"
  }
  "Release" {
    $env:CMAKE_BUILD_CONFIG = "RELEASE"
  }
  default {
    throw "Unsupported build configuration: ${env:CONFIGURATION}"
  }
}

$env:CMAKE_GENERATOR_PLATFORM = ""
switch (${env:TOOLCHAIN}) {
  "msvc" {
    $cmake_generator_msvc_version_suffix = " ${env:MSVC_VERSION}" -replace "([\d]+)\.([\d]+)", '$1'
    switch (${env:MSVC_VERSION}) {
      "14.2" {
        $cmake_generator_msvc_version_suffix = " 16 2019"
      }
      "14.1" {
        $cmake_generator_msvc_version_suffix = " 15 2017"
      }
      "14.0" {
        $cmake_generator_msvc_version_suffix = "${cmake_generator_msvc_version_suffix} 2015"
      }
      "12.0" {
        $cmake_generator_msvc_version_suffix = "${cmake_generator_msvc_version_suffix} 2013"
      }
      "11.0" {
        $cmake_generator_msvc_version_suffix = "${cmake_generator_msvc_version_suffix} 2012"
      }
      "10.0" {
        $cmake_generator_msvc_version_suffix = "${cmake_generator_msvc_version_suffix} 2010"
      }
      "9.0" {
        $cmake_generator_msvc_version_suffix = "${cmake_generator_msvc_version_suffix} 2008"
      }
      default {
        throw "Unsupported ${env:TOOLCHAIN} version for CMake generator: ${env:MSVC_VERSION}"
      }
    }
    switch (${env:PLATFORM}) {
      "x86" {
        $env:CMAKE_GENERATOR_PLATFORM = "Win32"
      }
      "x64" {
        $env:CMAKE_GENERATOR_PLATFORM = "x64"
      }
      default {
        throw "Unsupported platform for CMake generator: ${env:PLATFORM}"
      }
    }
    $env:CMAKE_GENERATOR = "Visual Studio${cmake_generator_msvc_version_suffix}"
  }
  "mingw" {
    $env:CMAKE_GENERATOR = "MinGW Makefiles"
  }
  "default" {
    throw "Unsupported toolchain for CMake generator: ${env:TOOLCHAIN}"
  }
}

$env:COVERAGE_BUILD = (${env:COVERAGE_BUILD_CANDIDATE} -eq "1") `
  -and (${env:CONFIGURATION} -eq "Debug") `
  -and (${env:PLATFORM} -eq "x64")
if ((${env:COVERAGE_BUILD} -eq "True") -and `
 -not (Test-Path -Path env:CODECOV_TOKEN) -or (${env:CODECOV_TOKEN} -eq "")) {
  throw "CODECOV_TOKEN environment variable is not defined but is required to upload coverage report to Codecov"
}
$env:CODECOV_FLAG = "windows_${env:OS_VERSION}__${env:PLATFORM}__${env:TOOLCHAIN_ID}"
$env:CODECOV_FLAG = "${env:CODECOV_FLAG}" -replace "[\.-]", "_"

Write-Host "PLATFORM                  : ${env:PLATFORM}"
Write-Host "CONFIGURATION             : ${env:CONFIGURATION}"
Write-Host "TOOLCHAIN_ID              : ${env:TOOLCHAIN_ID}"
switch (${env:TOOLCHAIN}) {
  "msvc" {
    Write-Host "MSVS_PATCH_FOLDER         : ${env:MSVS_PATCH_FOLDER}"
    Write-Host "MSVS_PATCH_BATCH_FILE     : ${env:MSVS_PATCH_BATCH_FILE}"
    Write-Host "WINDOWS_SDK_ENV_BATCH_FILE: ${env:WINDOWS_SDK_ENV_BATCH_FILE}"
    Write-Host "WINDOWS_SDK_ENV_PARAMETERS: ${env:WINDOWS_SDK_ENV_PARAMETERS}"
    Write-Host "MSVC_VARS_BATCH_FILE      : ${env:MSVC_VARS_BATCH_FILE}"
    Write-Host "MSVC_VARS_PLATFORM        : ${env:MSVC_VARS_PLATFORM}"
  }
  "mingw" {
    Write-Host "MINGW_HOME                : ${env:MINGW_HOME}"
  }
}
Write-Host "APPVEYOR_BUILD_FOLDER     : ${env:APPVEYOR_BUILD_FOLDER}"
Write-Host "ARTIFACT_PATH_SUFFIX      : ${env:ARTIFACT_PATH_SUFFIX}"
Write-Host "CMAKE_GENERATOR           : ${env:CMAKE_GENERATOR}"
Write-Host "CMAKE_GENERATOR_PLATFORM  : ${env:CMAKE_GENERATOR_PLATFORM}"
Write-Host "COVERAGE_BUILD            : ${env:COVERAGE_BUILD}"
Write-Host "CODECOV_FLAG              : ${env:CODECOV_FLAG}"
if (${env:COVERAGE_BUILD} -eq "True") {
  Write-Host "COBERTURA_COVERAGE_FILE   : ${env:COBERTURA_COVERAGE_FILE}"
}

if (${env:COVERAGE_BUILD} -eq "True") {
  Write-Host "Installing OpenCppCoverage from Chocolatey package"
  appveyor-retry choco install -y --no-progress opencppcoverage
  if (${LastExitCode} -ne 0) {
    throw "Installation of OpenCppCoverage Chocolatey package failed with ${LastExitCode} exit code"
  }
  Write-Host "OpenCppCoverage installed"

  Write-Host "Installing Codecov from pip package"
  pip install --disable-pip-version-check --retries "${env:PIP_RETRY}" codecov=="${env:CODECOV_VERSION}"
  if (${LastExitCode} -ne 0) {
    throw "Installation of Codecov pip package failed with exit code ${LastExitCode}"
  }
  Write-Host "Codecov installed"
}

if (Test-Path env:MSVS_PATCH_FOLDER) {
  Set-Location -Path "${env:MSVS_PATCH_FOLDER}"
}
if (Test-Path env:MSVS_PATCH_BATCH_FILE) {
  Write-Host "Patching MSVS with ${env:MSVS_PATCH_BATCH_FILE}"
  & "${env:MSVS_PATCH_BATCH_FILE}"
  if (${LastExitCode} -ne 0) {
    throw "Patch of MSVC failed with exit code ${LastExitCode}"
  }
  Write-Host "Patching of MSVS with completed successfully"
}

Set-Location -Path "${env:APPVEYOR_BUILD_FOLDER}"
