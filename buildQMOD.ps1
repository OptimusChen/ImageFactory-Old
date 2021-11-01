# Builds a .qmod file for loading with QuestPatcher
$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

$ArchiveName = "ImageFactory_v0.1.0.qmod"
$TempArchiveName = "ImageFactory_v0.1.0.qmod.zip"

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk
Compress-Archive -Path "./libs/arm64-v8a/libImageFactory.so", "./libs/arm64-v8a/libbeatsaber-hook_2_3_2.so", "./mod.json", "./bsmg.png", "./pixel.png", "./auros.png", "./bandoot.png", "./github.png", "./help.png", "./logo.png", "./reset.png", "./settings.png", "./aurosActive.png", "./bandootActive.png", "./githubActive.png", "./helpActive.png", "./resetActive.png", "./settingsActive.png" -DestinationPath $TempArchiveName -Force
Move-Item $TempArchiveName $ArchiveName -Force