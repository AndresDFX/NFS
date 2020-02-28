# -*- mode: ruby -*-
# vi: set ft=ruby :

#VBoxManage controlvm "andresdfx_nfs" natpf1 "redUDP,udp,,5000,,5000" --->Instruccion para crear un portforwarding

Vagrant.configure("2") do |web|
    web.vm.box = "ubuntu/xenial64"
    web.vm.provision "file", source: "scripts/server-udp.py", destination: "/home/vagrant/"
    web.vm.provision "shell", path: "script.sh"
    web.vm.network "forwarded_port", guest: 80, host: 9000, protocol: "tcp"
    web.vm.network "forwarded_port", guest: 81, host: 9001, protocol: "udp"
    web.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--name', 'andresdfx_nfs' ]
      vb.customize [ 'modifyvm', :id, '--memory', '386' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
      end
  end

 