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

    public function test_create() {
        $this->reset_sockets();
        $auth = new ZAuth();
        $this->assertNotNull($auth);
    }

    public function test_no_auth() {
        $auth = new ZAuth();
        $this->reset_sockets();
        $this->assertTrue($this->can_connect());
    }

    public function test_zap_domain_allow_all() {
        $auth = new ZAuth();
        $this->reset_sockets();
        $this->server->set_zap_domain("global");
        $this->assertTrue($this->can_connect());
    }


    public function test_zap_domain_deny_localhost() {
        $auth = new ZAuth();

        $this->reset_sockets();
        $this->server->set_zap_domain("global");
        $auth->deny("127.0.0.1");
        $this->assertFalse($this->can_connect());
    }

    public function test_zap_domain_allow_localhost() {
        $auth = new ZAuth();

        $this->reset_sockets();
        $this->server->set_zap_domain("global");
        $auth->allow("127.0.0.1");
        $this->assertTrue($this->can_connect());
    }

    public function test_plain_no_auth() {
        $auth = new ZAuth();

        // PLAIN
        $this->reset_sockets();
        $this->server->set_plain_server(true);
        $this->client->set_plain_username("admin");
        $this->client->set_plain_password("password");
        $this->assertFalse($this->can_connect());
    }

    public function test_plain_auth_ok() {
        $auth = new ZAuth();

        // PLAIN WITH PW
        $this->reset_sockets();
        file_put_contents(static::cert_dir ."/passwords", "admin=password");
        $this->server->set_plain_server(true);
        $auth->configure(ZAuth::AUTH_PLAIN, static::cert_dir ."/passwords");
        $this->client->set_plain_username("admin");
        $this->client->set_plain_password("password");
        $this->assertTrue($this->can_connect());
    }

    public function test_plain_auth_error() {
        $auth = new ZAuth();

        // PLAIN WITH PW ERROR
        $this->reset_sockets();
        $this->server->set_plain_server(true);
        $auth->configure(ZAuth::AUTH_PLAIN, static::cert_dir ."/passwords");
        $this->client->set_plain_username("admin");
        $this->client->set_plain_password("bogus");
        $this->assertFalse($this->can_connect());
    }

    /*
    public function test_curve_auth_all() {
        $auth = new ZAuth();

        if(ZSys::has_curve()) {
            $this->reset_sockets();

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
            $auth->configure(ZAuth::AUTH_CURVE, "*");
            $this->assertTrue($this->can_connect());
            $this->reset_sockets();

            //  Test full client authentication using certificates
            $server_cert->apply($this->server);
            $client_cert->apply($this->client);
            $this->server->set_curve_server(true);
            $this->client->set_curve_serverkey($server_key);
            $client_cert->save_public(static::cert_dir ."/mycert.txt");
            $auth->configure(ZAuth::AUTH_CURVE, static::cert_dir);
            $this->assertTrue($this->can_connect());

        }

    }

    */

    private function reset_sockets() {
        $this->server = new ZSocket(ZSys::SOCKET_PUSH);
        $this->client = new ZSocket(ZSys::SOCKET_PULL);
        $this->client->set_rcvtimeo(500);
    }

    private function can_connect() {
        $port = $this->server->bind("tcp://127.0.0.1:*");
        $success = $this->client->connect("tcp://127.0.0.1:" . $port);
        $this->server->send_string("hello");
        $success = $success && ("hello" == $this->client->recv_string());
        return $success;
    }


}