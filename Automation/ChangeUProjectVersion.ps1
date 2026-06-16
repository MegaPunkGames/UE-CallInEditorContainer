param(
     [Parameter(Mandatory)]
     [ValidateLength(3,3)]
     [ValidatePattern('\d\.\d')]
     [string]$Version)

echo "Changing target engine to version $Version"
$command = "(Get-Content '../CIEContainer.uproject') -replace '`"EngineAssociation`": `"\d{1}`.\d{1}`"', '`"EngineAssociation`": `"$Version`"' | Out-File -Encoding utf8 '../CIEContainer.uproject'"

Invoke-Expression $command