<?php

class ZSocketTest extends \PHPUnit_Framework_TestCase
{

    private $socket;

    private $rep;
    private $req;

    private $rep_pair;
    private $req_pair;

    protected function setUp()
    {

        // $this->markTestSkipped('must be revisited.');

        $endpoint = "ipc:///tmp/rep";
        $rep = new ZSocket(ZSys::SOCKET_REP);
        $rep->bind($endpoint);
        $req = new ZSocket(ZSys::SOCKET_REQ);
        $req->connect($endpoint);

        $endpoint = "ipc:///tmp/pair";
        $rep_pair = new ZSocket(ZSys::SOCKET_PAIR);
        $rep_pair->bind($endpoint);
        $req_pair = new ZSocket(ZSys::SOCKET_PAIR);
        $req_pair->connect($endpoint);

        usleep(50000);

        $this->rep = $rep;
        $this->req = $req;
        $this->rep_pair = $rep_pair;
        $this->req_pair = $req_pair;

        $this->socket = $rep;
    }

    private function send_recv($type, $data)
    {
        $this->req->send_picture($type, $data);
        $result = $this->rep->recv_picture($type);
        return $result[0] == $data;
    }

    private function send_recv_pair($type, $data)
    {
        $this->req_pair->send_picture($type, $data);
        $result = $this->rep_pair->recv_picture($type);
        return $result[0] == $data;
    }

    public function test_create_sockets()
    {
        $socket_types = ['pair', 'rep', 'req', 'push', 'pull', 'pub', 'sub', 'router', 'dealer', 'xpub', 'xsub', 'xrep', 'xreq', 'stream'];
        $result = true;
        foreach ($socket_types as $socket_type) {
            $socket = new ZSocket($socket_type);
            $result = $result && ($socket !== null);
        }
        $this->assertTrue($result);
    }

    public function test_create_invalid_sockets()
    {
        $result = true;
        try {
            $socket = new ZSocket("gino");
        } catch (Exception $e) {
            $result = false;
        }
        $this->assertFalse($result);
    }

    public function test_create_sockets_static()
    {
        // $this->assertNotNull(ZSocket::pair("inproc://tesinproc"));
        $this->assertNotNull(ZSocket::rep("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::req("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::push("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::pull("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::pub("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::sub("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::router("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::dealer("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::xpub("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::xsub("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::xrep("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::xreq("ipc:///tmp/test"));
        $this->assertNotNull(ZSocket::stream("ipc:///tmp/test"));
    }

    public function test_get_options()
    {
        $options = $this->req->get_options();
        $this->assertArrayHasKey("last_endpoint", $options);

    }

    public function test_send_recv_string() {
        $this->req->send_string("hello");
        $result = $this->rep->recv_string();
        $this->assertEquals($result, "hello");
    }

    public function test_send_recv_msg() {
        $send = new ZMsg();
        $send->append_string("hello");
        $send->append_string("world");
        $this->req->send($send);

        $recv = $this->rep->recv();

        $this->assertNotNull($recv);
        $this->assertEquals(get_class($recv), "ZMsg");
        $this->assertTrue($send->get_size() == 2 && $recv->get_size() == 2);
        $this->assertEquals($recv->pop_string(), "hello");
        $this->assertEquals($recv->pop_string(), "world");
    }

    public function test_send_recv_picture_multi()
    {
        $msg = new ZMsg();

        $success = [
            '1' => pow(2, 8) - 1,                           // 1 = 8 bit unsigned
            '2' => pow(2, 15) - 1,                          // 2 = 16 bit signed
            '4' => pow(2, 31) - 1,                          // 4 = 32 bit signed
            '8' => pow(2, 63) - 1,                          // 8 = 64 bit signed
            'i' => pow(2, 31) - 1,                          // i = 32bit signed
            'u' => pow(2, 32) - 1,                          // u = 32 bit unsigned
            's' => str_pad('-', 255, '-'),                  // s = short string (255 chars)
            'S' => str_pad('-', 256, '-'),                  // S = long string (> 255 chars),
            'b' => pack("nvc*", 0x1234, 0x5678, 65, 66),    // b = byte buffer
            'z' => null,                                    // z = NULL
            'm' => $msg,                                    // ZMsg (collect frames not in picture, till the end of recieved message)
        ];

        $picture_idx = array_keys($success);
        $picture = implode("", $picture_idx);
        $params = array_merge([$picture], array_values($success));
        call_user_func_array([$this->req, 'send_picture'], $params);
        $result = $this->rep->recv_picture($picture);

       // print_r([$success, $result]);

        $equals = true;
        foreach ($result as $idx => $value) {
            $success_value = $success[$picture_idx[$idx]];
            if (is_object($success_value))
                $equals = ($equals && (get_class($value) === get_class($success_value)));
            else
                $equals = ($equals && ($value == $success_value));
        }
        $this->assertTrue($equals);
    }


    // Test picture type 'i' againts a zero - checking success
    public function test_send_recv_picture_i_zero() {
        $this->assertTrue($this->send_recv('i', 0));
    }

// Test picture type 'i' againts a s8bit - checking success
    public function test_send_recv_picture_i_s8bit() {
        $this->assertTrue($this->send_recv('i', pow(2,7) - 1));
    }

// Test picture type 'i' againts a u8bit - checking success
    public function test_send_recv_picture_i_u8bit() {
        $this->assertTrue($this->send_recv('i', pow(2,8) - 1));
    }

// Test picture type 'i' againts a s16bit - checking success
    public function test_send_recv_picture_i_s16bit() {
        $this->assertTrue($this->send_recv('i', pow(2,15) - 1));
    }

// Test picture type 'i' againts a u16bit - checking success
    public function test_send_recv_picture_i_u16bit() {
        $this->assertTrue($this->send_recv('i', pow(2,16) - 1));
    }

// Test picture type 'i' againts a s32bit - checking success
    public function test_send_recv_picture_i_s32bit() {
        $this->assertTrue($this->send_recv('i', pow(2,31) - 1));
    }

// Test picture type 'i' againts a u32bit - checking failure
    public function test_send_recv_picture_i_u32bit() {
        $this->assertFalse($this->send_recv('i', pow(2,32) - 1));
    }

// Test picture type 'i' againts a s64bit - checking failure
    public function test_send_recv_picture_i_s64bit() {
        $this->assertFalse($this->send_recv('i', pow(2,63) - 1));
    }

// Test picture type 'i' againts a u64bit - checking failure
    public function test_send_recv_picture_i_u64bit() {
        $this->assertFalse($this->send_recv('i', pow(2,64) - 1));
    }

// Test picture type 'i' againts a maxint - checking failure
    public function test_send_recv_picture_i_maxint() {
        $this->assertFalse($this->send_recv('i', PHP_INT_MAX));
    }

// Test picture type '1' againts a zero - checking success
    public function test_send_recv_picture_1_zero() {
        $this->assertTrue($this->send_recv('1', 0));
    }

// Test picture type '1' againts a s8bit - checking success
    public function test_send_recv_picture_1_s8bit() {
        $this->assertTrue($this->send_recv('1', pow(2,7) - 1));
    }

// Test picture type '1' againts a u8bit - checking success
    public function test_send_recv_picture_1_u8bit() {
        $this->assertTrue($this->send_recv('1', pow(2,8) - 1));
    }

// Test picture type '1' againts a s16bit - checking failure
    public function test_send_recv_picture_1_s16bit() {
        $this->assertFalse($this->send_recv('1', pow(2,15) - 1));
    }

// Test picture type '1' againts a u16bit - checking failure
    public function test_send_recv_picture_1_u16bit() {
        $this->assertFalse($this->send_recv('1', pow(2,16) - 1));
    }

// Test picture type '1' againts a s32bit - checking failure
    public function test_send_recv_picture_1_s32bit() {
        $this->assertFalse($this->send_recv('1', pow(2,31) - 1));
    }

// Test picture type '1' againts a u32bit - checking failure
    public function test_send_recv_picture_1_u32bit() {
        $this->assertFalse($this->send_recv('1', pow(2,32) - 1));
    }

// Test picture type '1' againts a s64bit - checking failure
    public function test_send_recv_picture_1_s64bit() {
        $this->assertFalse($this->send_recv('1', pow(2,63) - 1));
    }

// Test picture type '1' againts a u64bit - checking failure
    public function test_send_recv_picture_1_u64bit() {
        $this->assertFalse($this->send_recv('1', pow(2,64) - 1));
    }

// Test picture type '1' againts a maxint - checking failure
    public function test_send_recv_picture_1_maxint() {
        $this->assertFalse($this->send_recv('1', PHP_INT_MAX));
    }

// Test picture type '2' againts a zero - checking success
    public function test_send_recv_picture_2_zero() {
        $this->assertTrue($this->send_recv('2', 0));
    }

// Test picture type '2' againts a s8bit - checking success
    public function test_send_recv_picture_2_s8bit() {
        $this->assertTrue($this->send_recv('2', pow(2,7) - 1));
    }

// Test picture type '2' againts a u8bit - checking success
    public function test_send_recv_picture_2_u8bit() {
        $this->assertTrue($this->send_recv('2', pow(2,8) - 1));
    }

// Test picture type '2' againts a s16bit - checking success
    public function test_send_recv_picture_2_s16bit() {
        $this->assertTrue($this->send_recv('2', pow(2,15) - 1));
    }

// Test picture type '2' againts a u16bit - checking failure
    public function test_send_recv_picture_2_u16bit() {
        $this->assertFalse($this->send_recv('2', pow(2,16) - 1));
    }

// Test picture type '2' againts a s32bit - checking failure
    public function test_send_recv_picture_2_s32bit() {
        $this->assertFalse($this->send_recv('2', pow(2,31) - 1));
    }

// Test picture type '2' againts a u32bit - checking failure
    public function test_send_recv_picture_2_u32bit() {
        $this->assertFalse($this->send_recv('2', pow(2,32) - 1));
    }

// Test picture type '2' againts a s64bit - checking failure
    public function test_send_recv_picture_2_s64bit() {
        $this->assertFalse($this->send_recv('2', pow(2,63) - 1));
    }

// Test picture type '2' againts a u64bit - checking failure
    public function test_send_recv_picture_2_u64bit() {
        $this->assertFalse($this->send_recv('2', pow(2,64) - 1));
    }

// Test picture type '2' againts a maxint - checking failure
    public function test_send_recv_picture_2_maxint() {
        $this->assertFalse($this->send_recv('2', PHP_INT_MAX));
    }

// Test picture type '4' againts a zero - checking success
    public function test_send_recv_picture_4_zero() {
        $this->assertTrue($this->send_recv('4', 0));
    }

// Test picture type '4' againts a s8bit - checking success
    public function test_send_recv_picture_4_s8bit() {
        $this->assertTrue($this->send_recv('4', pow(2,7) - 1));
    }

// Test picture type '4' againts a u8bit - checking success
    public function test_send_recv_picture_4_u8bit() {
        $this->assertTrue($this->send_recv('4', pow(2,8) - 1));
    }

// Test picture type '4' againts a s16bit - checking success
    public function test_send_recv_picture_4_s16bit() {
        $this->assertTrue($this->send_recv('4', pow(2,15) - 1));
    }

// Test picture type '4' againts a u16bit - checking success
    public function test_send_recv_picture_4_u16bit() {
        $this->assertTrue($this->send_recv('4', pow(2,16) - 1));
    }

// Test picture type '4' againts a s32bit - checking success
    public function test_send_recv_picture_4_s32bit() {
        $this->assertTrue($this->send_recv('4', pow(2,31) - 1));
    }

// Test picture type '4' againts a u32bit - checking failure
    public function test_send_recv_picture_4_u32bit() {
        $this->assertFalse($this->send_recv('4', pow(2,32) - 1));
    }

// Test picture type '4' againts a s64bit - checking failure
    public function test_send_recv_picture_4_s64bit() {
        $this->assertFalse($this->send_recv('4', pow(2,63) - 1));
    }

// Test picture type '4' againts a u64bit - checking failure
    public function test_send_recv_picture_4_u64bit() {
        $this->assertFalse($this->send_recv('4', pow(2,64) - 1));
    }

// Test picture type '4' againts a maxint - checking failure
    public function test_send_recv_picture_4_maxint() {
        $this->assertFalse($this->send_recv('4', PHP_INT_MAX));
    }

// Test picture type '8' againts a zero - checking success
    public function test_send_recv_picture_8_zero() {
        $this->assertTrue($this->send_recv('8', 0));
    }

// Test picture type '8' againts a s8bit - checking success
    public function test_send_recv_picture_8_s8bit() {
        $this->assertTrue($this->send_recv('8', pow(2,7) - 1));
    }

// Test picture type '8' againts a u8bit - checking success
    public function test_send_recv_picture_8_u8bit() {
        $this->assertTrue($this->send_recv('8', pow(2,8) - 1));
    }

// Test picture type '8' againts a s16bit - checking success
    public function test_send_recv_picture_8_s16bit() {
        $this->assertTrue($this->send_recv('8', pow(2,15) - 1));
    }

// Test picture type '8' againts a u16bit - checking success
    public function test_send_recv_picture_8_u16bit() {
        $this->assertTrue($this->send_recv('8', pow(2,16) - 1));
    }

// Test picture type '8' againts a s32bit - checking success
    public function test_send_recv_picture_8_s32bit() {
        $this->assertTrue($this->send_recv('8', pow(2,31) - 1));
    }

// Test picture type '8' againts a u32bit - checking success
    public function test_send_recv_picture_8_u32bit() {
        $this->assertTrue($this->send_recv('8', pow(2,32) - 1));
    }

// Test picture type '8' againts a s64bit - checking success
    public function test_send_recv_picture_8_s64bit() {
        $this->assertTrue($this->send_recv('8', pow(2,63) - 1));
    }

// Test picture type '8' againts a u64bit - checking failure
    public function test_send_recv_picture_8_u64bit() {
        $this->assertFalse($this->send_recv('8', pow(2,64) - 1));
    }

// Test picture type '8' againts a maxint - checking success
    public function test_send_recv_picture_8_maxint() {
        $this->assertTrue($this->send_recv('8', PHP_INT_MAX));
    }

// Test picture type 'u' againts a zero - checking success
    public function test_send_recv_picture_u_zero() {
        $this->assertTrue($this->send_recv('u', 0));
    }

// Test picture type 'u' againts a s8bit - checking success
    public function test_send_recv_picture_u_s8bit() {
        $this->assertTrue($this->send_recv('u', pow(2,7) - 1));
    }

// Test picture type 'u' againts a u8bit - checking success
    public function test_send_recv_picture_u_u8bit() {
        $this->assertTrue($this->send_recv('u', pow(2,8) - 1));
    }

// Test picture type 'u' againts a s16bit - checking success
    public function test_send_recv_picture_u_s16bit() {
        $this->assertTrue($this->send_recv('u', pow(2,15) - 1));
    }

// Test picture type 'u' againts a u16bit - checking success
    public function test_send_recv_picture_u_u16bit() {
        $this->assertTrue($this->send_recv('u', pow(2,16) - 1));
    }

// Test picture type 'u' againts a s32bit - checking success
    public function test_send_recv_picture_u_s32bit() {
        $this->assertTrue($this->send_recv('u', pow(2,31) - 1));
    }

// Test picture type 'u' againts a u32bit - checking success
    public function test_send_recv_picture_u_u32bit() {
        $this->assertTrue($this->send_recv('u', pow(2,32) - 1));
    }

// Test picture type 'u' againts a s64bit - checking failure
    public function test_send_recv_picture_u_s64bit() {
        $this->assertFalse($this->send_recv('u', pow(2,63) - 1));
    }

// Test picture type 'u' againts a u64bit - checking failure
    public function test_send_recv_picture_u_u64bit() {
        $this->assertFalse($this->send_recv('u', pow(2,64) - 1));
    }

// Test picture type 'u' againts a maxint - checking failure
    public function test_send_recv_picture_u_maxint() {
        $this->assertFalse($this->send_recv('u', PHP_INT_MAX));
    }

// Test picture type 's' againts a empty_string - checking success
    public function test_send_recv_picture_s_empty_string() {
        $this->assertTrue($this->send_recv('s', ""));
    }

// Test picture type 's' againts a short_string - checking success
    public function test_send_recv_picture_s_short_string() {
        $this->assertTrue($this->send_recv('s', "ciao"));
    }

// Test picture type 's' againts a long_string - checking failure
    public function test_send_recv_picture_s_long_string() {
        $this->assertFalse($this->send_recv('s', str_pad('-', 1024)));
    }

// Test picture type 'S' againts a empty_string - checking success
    public function test_send_recv_picture_s_uppercase_empty_string() {
        $this->assertTrue($this->send_recv('S', ""));
    }

// Test picture type 'S' againts a short_string - checking success
    public function test_send_recv_picture_s_uppercase_short_string() {
        $this->assertTrue($this->send_recv('S', "ciao"));
    }

// Test picture type 'S' againts a long_string - checking success
    public function test_send_recv_picture_s_uppercase_long_string() {
        $this->assertTrue($this->send_recv('S', str_pad('-', 1024)));
    }


}