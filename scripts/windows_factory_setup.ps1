
$avrdude_url = "https://github.com/mariusgreuel/avrdude/releases/download/v6.3.1.1-windows/avrdude-v6.3.1.1-windows.zip"
$avrdudeZipFile = "$($pwd)\avrdude_zipped_folder.zip"
$unzip_target_directory = "$($pwd)\avrdude"
if (-not (Test-Path -Path "$unzip_target_directory/avrdude.exe" -PathType Leaf)) {
    Write-Output "Downloading avrdude executable for Windows..."
    Invoke-Webrequest $avrdude_url -OutFile $avrdudeZipFile
    Expand-Archive -Path $avrdudeZipFile -DestinationPath $unzip_target_directory -Force
    Remove-Item $avrdudeZipFile
}
Set-Alias -Name "avrdude" -Value ".\avrdude\avrdude.exe"
Read-Host "Please plug in USBasp dongle. Hit ENTER to continue..."

avrdude -c USBasp -p m32u4 -B 10 -U lfuse:w:0xFF:m -U hfuse:w:0xD8:m -U efuse:w:0xCB:m -U lock:w:0xFF:m
avrdude -v -c USBasp -p m32u4 -P usb -U flash:w:Caterina-Micro.hex:i -U lock:w:0x2F:m

Read-Host "Please remove USBAsp dongle and plug in micro-usb cable. Hit ENTER to continue"

$connected_port = [System.IO.Ports.SerialPort]::getportnames()
if ($connected_port) {
    Write-Host $device.Name "(Manufacturer:"$device.Manufacturer")"
    avrdude -v -p m32u4 -c avr109 -P $connected_port -b 57600 -D -U flash:w:zoom_button_osx.hex:i
}
else {
    Write-Host "USB connection not found - Did you remember to disconnect the USBAsp dongle and connect the micro-usb cable?"
}
