<?php

class ZCertTest extends \PHPUnit_Framework_TestCase {

    const cert_dir  = "./.certdir";
    const cert_file = "certfile.txt";

    public static function setUpBeforeClass() {
        exec("mkdir -p " . static::cert_dir);
    }

    public static function tearDownAfterClass() {
        exec("rm -rf " . static::cert_dir);
    }

    public function test_create() {
         $cert = new ZCert();
         $this->assertNotNull($cert);
    }

    public function test_save() {
        $cert = new ZCert();
        $cert->save(static::cert_dir . "/" . static::cert_file);
        $this->assertFileExists(static::cert_dir . "/" . static::cert_file);
    }

    public function test_load() {
        $cert = new ZCert(static::cert_dir . "/" . static::cert_file);
        $this->assertNotNull($cert);
        $this->assertNotEmpty($cert->get_public_key_txt());
    }

    public function test_load_save() {

        ## SAVE
        $cert = new ZCert();
        $cert->save(static::cert_dir . "/" . static::cert_file . "_load_save");
        $this->assertFileExists(static::cert_dir . "/" . static::cert_file . "_load_save");

        ## LOAD
        $cert2 = new ZCert(static::cert_dir . "/" . static::cert_file . "_load_save");
        $this->assertNotNull($cert2);

        ## SAME CERT?
        $cert_pk        = $cert->get_public_key_txt();
        $cert_pk2       = $cert2->get_public_key_txt();
        $cert_pk_bin    = $cert->get_public_key();
        $cert_pk2_bin   = $cert2->get_public_key();

        $this->assertNotEmpty($cert_pk);
        $this->assertNotEmpty($cert_pk2);
        $this->assertEquals($cert_pk, $cert_pk2);

    }

    public function test_meta() {
        $cert = new ZCert();
        $cert->set_meta('email', "ph@imatix.com");
        $cert->set_meta('name', "Pieter Hintjens");
        $cert->set_meta('organization', "iMatix Corporation");
        $cert->set_meta('version', 1);
        $this->assertEquals($cert->get_meta('email'),"ph@imatix.com");
        $cert_keys = $cert->get_meta_keys();
        $this->assertEquals(count($cert_keys),4);
    }


}