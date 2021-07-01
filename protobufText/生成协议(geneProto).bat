protoc.exe ./login.proto --cpp_out=../server/gen_proto
protoc.exe ./lottery.proto --cpp_out=../server/gen_proto
protoc.exe ./scene.proto --cpp_out=../server/gen_proto
protoc.exe ./dungeon.proto --cpp_out=../server/gen_proto
protoc.exe ./entity.proto --cpp_out=../server/gen_proto
protoc.exe ./PlayerArchive.proto --cpp_out=../server/gen_proto
protoc.exe ./backpack.proto --cpp_out=../server/gen_proto
protoc.exe ./server.proto --cpp_out=../server/gen_proto
protoc.exe ./quest.proto --cpp_out=../server/gen_proto
protoc.exe ./pet.proto --cpp_out=../server/gen_proto
protoc.exe ./mail.proto --cpp_out=../server/gen_proto
protoc.exe ./mall.proto --cpp_out=../server/gen_proto
protoc.exe ./mounts.proto --cpp_out=../server/gen_proto
protoc.exe ./npc.proto --cpp_out=../server/gen_proto
protoc.exe ./team.proto --cpp_out=../server/gen_proto
protoc.exe ./chat.proto --cpp_out=../server/gen_proto
protoc.exe ./pvp.proto --cpp_out=../server/gen_proto
protoc.exe ./boss.proto --cpp_out=../server/gen_proto
protoc.exe ./server_chat.proto --cpp_out=../server/gen_proto
protoc.exe ./login_server.proto --cpp_out=../server/gen_proto
protoc.exe ./list_server.proto --cpp_out=../server/gen_proto
protoc.exe ./server_gate.proto --cpp_out=../server/gen_proto
protoc.exe ./server_game.proto --cpp_out=../server/gen_proto
protoc.exe ./server_master.proto --cpp_out=../server/gen_proto

cd ../server/gen_proto
