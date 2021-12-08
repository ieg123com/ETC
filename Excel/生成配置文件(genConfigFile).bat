echo 开始生成配置

config_build.exe ./ --out_type=auto_gen_cpp --json_out=../Conf/ --cpp_out=../Server/model/config/ --read_conf_path=Conf/

echo 配置生成完成
pause