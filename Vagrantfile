# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.env.enable  
  config.vm.box = ENV['BOX_NAME']
  
  config.vm.define "server" do |web|
    web.vm.network "private_network", ip: ENV['IP_SERVER']
    web.vm.provision "file", source: "scripts_socket/server-udp.py", destination: "$HOME/server-udp.py"
    web.vm.provision "shell", path: "server.sh"
    web.vm.network "forwarded_port", guest: 9100, host: 9100, protocol: "tcp"
    web.vm.network "forwarded_port", guest: 5678, host: 5678, protocol: "udp"
    web.vm.synced_folder "./shared", "/mnt/sharedfolder" 
    web.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--name', 'server' ]
      vb.customize [ 'modifyvm', :id, '--memory', '782' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
    end
  end
  
  config.vm.define "client01" do |web|
    web.vm.network "private_network", ip: ENV['IP_CLIENT1']
    web.vm.provision "shell", path: "client.sh"
    web.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--memory', '386' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
      vb.customize [ 'modifyvm', :id, '--name', 'client01' ]
    end
  end

  config.vm.define "client02" do |web|
    web.vm.network "private_network", ip: ENV['IP_CLIENT2']
    web.vm.provision "shell", path: "client.sh"
    web.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--memory', '386' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
      vb.customize [ 'modifyvm', :id, '--name', 'client02' ]
    end
  end

end 

 