# -*- mode: ruby -*-
# vi: set ft=ruby :

#VBoxManage controlvm "andresdfx_nfs" natpf1 "redUDP,udp,,5679,,5679" -->Instruccion para crear un portforwarding
Vagrant.configure("2") do |config|
    config.vm.box = "ubuntu/xenial64"
    config.vm.define "server_nfs" do |web|
      web.vm.network "private_network", ip: "192.168.100.5"
      web.vm.provision "file", source: "scripts/server-udp.py", destination: "$HOME/server-udp.py"
      web.vm.provision "shell", path: "server.sh"
      web.vm.network "forwarded_port", guest: 1234, host: 1234, protocol: "tcp"
      web.vm.network "forwarded_port", guest: 5678, host: 5678, protocol: "udp"
      web.vm.synced_folder "./shared", "/mnt/sharedfolder" 
      web.vm.provider :virtualbox do |vb|
        vb.customize [ 'modifyvm', :id, '--name', 'server_nfs' ]
        vb.customize [ 'modifyvm', :id, '--memory', '782' ]
        vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
      end
    end

  config.vm.define "client01" do |web|
    web.vm.network "private_network", ip: "192.168.100.4"
    web.vm.provision "shell", path: "client.sh"
    web.vm.synced_folder "./shared", "/mnt/sharedfolder_client" 
    web.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--memory', '386' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
      vb.customize [ 'modifyvm', :id, '--name', 'client01' ]
    end
  end

  config.vm.define "client02" do |web|
    web.vm.network "private_network", ip: "192.168.100.3"
    web.vm.provision "shell", path: "client.sh"
    web.vm.synced_folder "./shared", "/mnt/sharedfolder_client" 
    web.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--memory', '386' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
      vb.customize [ 'modifyvm', :id, '--name', 'client02' ]
    end
  end
end 

 