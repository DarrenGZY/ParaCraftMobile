cls
REM rm all asset file since some may be readonly
rd "frameworks\runtime-src\proj.android\assets" /s /q

call UpdateResourceScript

cocos run -p android