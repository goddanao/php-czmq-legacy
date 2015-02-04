<?php

class ZAuthTest extends \PHPUnit_Framework_TestCase {

    private $server;
    private $client;

    const cert_dir  = "./.certdir";

    public static function setUpBeforeClass() {
        exec("mkdir -p " . static::cert_dir);
    }

    public static function tearDownAfterClass() {
        exec("rm -rf " . static::cert_dir);
    }

    public function test_all() {

        $auth = new ZAuth();
        // $auth->set_verbose();

        $this->reset_sockets();
        $this->assertTrue($this->can_connect());

        $this->reset_sockets();
        $this->server->set_zap_domain("global");
        $this->assertTrue($this->can_connect());

        $this->reset_sockets();
        $this->server->set_zap_domain("global");
        $auth->deny("127.0.0.1");
        $this->assertFalse($this->can_connect());

        $this->reset_sockets();
        $this->server->set_zap_domain("global");
        $auth->allow("127.0.0.1");
        $this->assertTrue($this->can_connect());
        $this->reset_sockets();

        // PLAIN
        $this->server->set_plain_server(true);
        $this->client->set_plain_username("admin");
        $this->client->set_plain_password("password");
        $this->assertFalse($this->can_connect());
        $this->reset_sockets();

        // PLAIN WITH PW
        file_put_contents(static::cert_dir ."/passwords", "admin=password");
        $this->server->set_plain_server(true);
        $auth->configure("PLAIN", static::cert_dir ."/passwords");
        $this->client->set_plain_username("admin");
        $this->client->set_plain_password("password");
        $this->assertTrue($this->can_connect());
        $this->reset_sockets();

        // PLAIN WITH PW ERROR
        $this->server->set_plain_server(true);
        $auth->configure("PLAIN", static::cert_dir ."/passwords");
        $this->client->set_plain_username("admin");
        $this->client->set_plain_password("bogus");
        $this->assertFalse($this->can_connect());
        $this->reset_sockets();

        if(ZSys::has_curve()) {

            $server_cert = new ZCert();
            $client_cert = new ZCert();
            $server_key = $server_cert->get_public_key_txt();

            //  Test without setting-up any authentication
            $server_cert->apply($this->server);
            $client_cert->apply($this->client);
            $this->server->set_curve_server(true);
            $this->client->set_curve_serverkey($server_key);
            $this->assertFalse($this->can_connect());
            $this->reset_sockets();

            //  Test CURVE_ALLOW_ANY
            $server_cert->apply($this->server);
            $client_cert->apply($this->client);
            $this->server->set_curve_server(true);
            $this->client->set_curve_serverkey($server_key);
            $auth->configure("CURVE", "*");
            $this->assertTrue($this->can_connect());
            $this->reset_sockets();

            //  Test full client authentication using certificates
            $server_cert->apply($this->server);
            $client_cert->apply($this->client);
            $this->server->set_curve_server(true);
            $this->client->set_curve_serverkey($server_key);
            $client_cert->save_public(static::cert_dir ."/mycert.txt");
            $auth->configure("CURVE", static::cert_dir);
            $this->assertTrue($this->can_connect());

        }

        $this->reset_sockets();
        $auth = null;

        $this->assertTrue($this->can_connect());
    }

    private function reset_sockets() {
        $this->server = new ZSocket(ZSys::SOCKET_PUSH);
        $this->client = new ZSocket(ZSys::SOCKET_PULL);
        $this->client->set_rcvtimeo(500);
    }

    private function can_connect() {
        $port = $this->server->bind("tcp://127.0.0.1:*");
        $success = $this->client->connect("tcp://127.0.0.1:" . $port);
        $this->server->send_string("hello");
        usleep(200);
        $success = $success && ("hello" == $this->client->recv_string());
        return $success;
    }
}