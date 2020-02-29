# -*- mode: ruby -*-
# vi: set ft=ruby :
#VBoxManage controlvm "andresdfx_nfs" natpf1 "redUDP,udp,,5679,,5679" -->Instruccion para crear un portforwarding

Vagrant.configure("2") do |web|
    web.vm.box = "ubuntu/xenial64"
    web.vm.provision "file", source: "scripts/server-udp.py", destination: "$HOME/server-udp.py"
    web.vm.provision "shell", path: "script.sh"
    web.vm.network "forwarded_port", guest: 1234, host: 1234, protocol: "tcp"
    web.vm.network "forwarded_port", guest: 5678, host: 5678, protocol: "udp"
    web.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--name', 'andresdfx_nfs' ]
      vb.customize [ 'modifyvm', :id, '--memory', '386' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
      end
  end

 