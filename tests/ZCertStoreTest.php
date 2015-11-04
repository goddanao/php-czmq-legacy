<?php

class ZCertStoreTest extends \PHPUnit_Framework_TestCase {

    const cert_dir  = "./.certdir";
    const cert_file = "certfile.txt";

    public static function setUpBeforeClass() {
        exec("mkdir -p " . static::cert_dir);
    }

    public static function tearDownAfterClass() {
        exec("rm -rf " . static::cert_dir);
    }

    public function test_create() {
        $cert = new ZCertStore();
        $this->assertNotNull($cert);
    }

    public function test_lookup_dir()
    {
        $cert1 = new ZCert();
        $cert1->save(static::cert_dir . "/" . static::cert_file . "_cert1");
        $cert2 = new ZCert();
        $cert2->save(static::cert_dir . "/" . static::cert_file . "_cert2");

        $store = new ZCertStore(static::cert_dir);

        $res = $store->lookup($cert1->get_public_key_txt());
        $this->assertEquals($res,$cert1);

    }

    public function test_lookup_memory()
    {
        $cert1 = new ZCert();
        $cert2 = new ZCert();
        $store = new ZCertStore();
        $store->insert($cert1);
        $store->insert($cert2);

        $res = $store->lookup($cert1->get_public_key_txt());
        $this->assertEquals($res,$cert1);

    }


}