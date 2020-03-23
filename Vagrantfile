# -*- mode: ruby -*-
# vi: set ft=ruby :

N = 2

Vagrant.configure("2") do |config|
  config.env.enable  
 
  config.vm.define "server" do |server|
    server.vm.box = ENV['BOX_NAME']
    server.vm.hostname = ENV['MASTER_NAME']
    server.vm.network "private_network", ip: ENV['IP_SERVER'], netmask:"255.255.0.0"
    server.vm.provision "shell", path: "general.sh"
    server.vm.provision "shell", path: "PART1_server.sh"
    server.vm.provision "shell", path: "PART2_server.sh"
    server.vm.provision "shell", path: "PART3_server.sh"
    server.vm.synced_folder "./shared", "/home/vagrant/shared",owner: "nobody", group: "nogroup"
    server.vm.network "forwarded_port", guest: ENV['TCP_PORT'] , host: ENV['TCP_PORT'] , protocol: "tcp"
    server.vm.network "forwarded_port", guest: ENV['UDP_PORT'] , host: ENV['UDP_PORT'] , protocol: "udp"
    server.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--name', ENV['MASTER_NAME'] ]
      vb.customize [ 'modifyvm', :id, '--memory', ENV['MEMORY_SERVER'] ]
      vb.customize [ 'modifyvm', :id, '--cpus', ENV['CPUS'] ]
    end
  end
  
  (1..N).each do |i|
    config.vm.define "client0#{i}" do |client|
        client.vm.box = ENV['BOX_NAME']
        client.vm.hostname = ENV['NODE_NAME']+"0#{i}"
        client.vm.network "private_network", ip: ENV['IP_BASE']+"#{i + 1}", netmask:"255.255.0.0"
        client.vm.provision "shell", path: "general.sh"
        client.vm.provision "shell", path: "PART2_client.sh"
        client.vm.provision "shell", path: "PART3_client.sh"  
        client.vm.synced_folder "./shared", "/home/vagrant/shared",owner: "nobody", group: "nogroup"
        client.vm.provider :virtualbox do |vb|
          vb.customize [ 'modifyvm', :id, '--name', ENV['NODE_NAME']+"0#{i}" ]
          vb.customize [ 'modifyvm', :id, '--memory', ENV['MEMORY_CLIENT'] ]
          vb.customize [ 'modifyvm', :id, '--cpus', ENV['CPUS']  ]
        end
    end
  end

end 

 