# -*- mode: ruby -*-
# vi: set ft=ruby :

N = 1

Vagrant.configure("2") do |config|
  config.env.enable  
  config.vm.box = ENV['BOX_NAME']
  
  config.vm.define "server" do |server|
    server.vm.network "private_network", ip: ENV['IP_BASE'] + "1"  
    server.vm.provision "shell", path: "general.sh"
    server.vm.provision "shell", path: "PART1_server.sh"
    server.vm.provision "shell", path: "PART2_server.sh"
    server.vm.provision "shell", path: "PART3_server.sh"
    server.vm.provision "file", source: "PART1/scripts_socket/server-udp.py", destination: "$HOME/server-udp.py"
    server.vm.network "forwarded_port", guest: ENV['TCP_PORT'] , host: ENV['TCP_PORT'] , protocol: "tcp"
    server.vm.network "forwarded_port", guest: ENV['UDP_PORT'] , host: ENV['UDP_PORT'] , protocol: "udp"
    server.vm.synced_folder "./shared", "/shared" 
    server.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--name', ENV['MASTER_NAME'] ]
      vb.customize [ 'modifyvm', :id, '--memory', '782' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
    end
  end
  
  (1..N).each do |i|
    config.vm.define "client0#{i}" do |client|
        client.vm.network "private_network", ip: ENV['IP_BASE']+"#{i + 1}"
        client.vm.provision "shell", path: "general.sh"
        client.vm.provision "shell", path: "PART2_client.sh"
        client.vm.provision "shell", path: "PART3_client.sh"
        client.vm.hostname = ENV['NODE_NAME']+"-#{i}"
        client.vm.provider :virtualbox do |vb|
          vb.customize [ 'modifyvm', :id, '--memory', '512' ]
          vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
          vb.customize [ 'modifyvm', :id, '--name', ENV['NODE_NAME']+"-#{i}" ]
        end
    end
  end

end 

 