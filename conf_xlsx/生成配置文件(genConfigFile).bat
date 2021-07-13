echo 开始生成配置

xlsx_to_json.exe ./ --out_type=auto_gen_cpp --json_out=../conf/ --cpp_out=../hotfix/config/ --read_conf_path=conf/

echo 配置生成完成
pause