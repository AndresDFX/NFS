# -*- mode: ruby -*-
# vi: set ft=ruby :
#VBoxManage controlvm "andresdfx_test" natpf1 "guestssh,udp,,5000,,5000"

Vagrant.configure("2") do |web|
    web.vm.box = "ubuntu/xenial64"
    web.vm.provision "shell", path: "script.sh"
    web.vm.provision "file", source: "/home/invitado/Escritorio/Vagrant/Scripts/server.py", destination: "/home/vagrant"
    web.vm.network "forwarded_port", guest: 80, host: 8080
    web.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--name', 'andresdfx_test' ]
      end
  end

 