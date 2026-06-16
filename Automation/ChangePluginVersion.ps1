param(
     [Parameter(Mandatory)]
     [string]$PluginFile,

     [Parameter(Mandatory)]
     [ValidateLength(3,5)]
     [ValidatePattern('\d\.\d.\d')]
     [string]$Version)

echo "Changing plugin version to $Version"
$command = "(Get-Content '$PluginFile') -replace '`"VersionName`": `"\d{1}`.\d{1}`.\d{1}`"', '`"VersionName`": `"$Version`"' | Out-File -Encoding utf8 '$PluginFile'"

Invoke-Expression $command