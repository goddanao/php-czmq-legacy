<?php

class ZMsgTest extends \PHPUnit_Framework_TestCase {

    public function test_create() {
        $msg = new ZMsg();
        $this->assertNotNull($msg);
    }

    public function test_traversable()
    {

        $msg = new ZMsg();

        $msg->append_string("Frame2");
        $msg->append_string("Frame3");
        $msg->prepend_string("Frame1");
        $msg->prepend_string("Frame0");

        $success = true;
        $i = 0;
        foreach($msg as $key => $value) {
            $success = $success && ($value == "Frame{$i}");
            $i++;
        }

        $this->assertEquals($i, 4);
        $this->assertTrue($success);
    }

        public function test_array_access() {

        $msg = new ZMsg();

        $msg->append_string("Frame2");
        $msg->append_string("Frame3");
        $msg->prepend_string("Frame1");
        $msg->prepend_string("Frame0");

        // Countable interface
        $this->assertEquals(count($msg), 4);

        // ArrayAccess interface
        $this->assertTrue($msg[0] == "Frame0");
        $this->assertTrue($msg[1] == "Frame1");

        $msg[3] = "test";
        unset($msg[2]);

        $this->assertEquals(count($msg), 3);
        $this->assertTrue($msg[2] == "test");

    }

    public function test_append_prepend_string() {

        $msg = new ZMsg();

        $msg->append_string("Frame2");
        $msg->append_string("Frame3");
        $msg->prepend_string("Frame1");
        $msg->prepend_string("Frame0");

        $this->assertEquals($msg->pop_string(), "Frame0");
        $this->assertEquals($msg->pop_string(), "Frame1");
        $this->assertEquals($msg->pop_string(), "Frame2");
        $this->assertEquals($msg->pop_string(), "Frame3");
        $this->assertNull($msg->pop_string());
    }

    public function test_append_prepend_picture() {

        $msg = new ZMsg();
        $msg->append_string("Frame0");

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
            // 'm' prende tutti i frame fino alla fine del messaggio e quindi non puo' essere usato in questo test )
            // 'm' => new ZMsg(),                           // ZMsg (collect frames not in picture, till the end of recieved message)
        ];

        $picture_idx = array_keys($success);
        $picture = implode("", $picture_idx);
        $params = array_merge([$picture], array_values($success));
        call_user_func_array([$msg, 'prepend_picture'], $params);

        $result = $msg->pop_picture($picture);

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

    public function test_first_next_last()
    {
        $msg = new ZMsg();

        $msg->append_string("Frame0");
        $msg->append_string("Frame1");
        $msg->append_string("Frame2");
        $msg->append_string("Frame3");

        $this->assertTrue($msg->last() == "Frame3");
        $this->assertTrue($msg->first() == "Frame0");
        $this->assertTrue($msg->next() ==  "Frame1");
        $this->assertTrue($msg->next() ==  "Frame2");
        $this->assertTrue($msg->next() ==  "Frame3");
        $frame = $msg->next();
        $this->assertNull($frame);

    }

}