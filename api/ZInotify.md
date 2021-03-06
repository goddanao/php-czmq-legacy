ZInotify
===============

ZInotify

Inotify watcher.


* Class name: ZInotify
* Namespace: 
* This class implements: [IZDescriptor](IZDescriptor.md)


Constants
----------


### IN_ACCESS

    const IN_ACCESS = 1





### IN_MODIFY

    const IN_MODIFY = 2





### IN_ATTRIB

    const IN_ATTRIB = 4





### IN_CLOSE_WRITE

    const IN_CLOSE_WRITE = 8





### IN_CLOSE_NOWRITE

    const IN_CLOSE_NOWRITE = 16





### IN_OPEN

    const IN_OPEN = 32





### IN_MOVED_FROM

    const IN_MOVED_FROM = 64





### IN_MOVED_TO

    const IN_MOVED_TO = 128





### IN_CREATE

    const IN_CREATE = 256





### IN_DELETE

    const IN_DELETE = 512





### IN_DELETE_SELF

    const IN_DELETE_SELF = 1024





### IN_MOVE_SELF

    const IN_MOVE_SELF = 2048





### IN_UNMOUNT

    const IN_UNMOUNT = 8192





### IN_Q_OVERFLOW

    const IN_Q_OVERFLOW = 16384





### IN_IGNORED

    const IN_IGNORED = 32768





### IN_CLOSE

    const IN_CLOSE = 24





### IN_MOVE

    const IN_MOVE = 192





### IN_ONLYDIR

    const IN_ONLYDIR = 16777216





### IN_DONT_FOLLOW

    const IN_DONT_FOLLOW = 33554432





### IN_EXCL_UNLINK

    const IN_EXCL_UNLINK = 67108864





### IN_MASK_ADD

    const IN_MASK_ADD = 536870912





### IN_ISDIR

    const IN_ISDIR = 1073741824





### IN_ONESHOT

    const IN_ONESHOT = 2147483648





### IN_ALL_EVENTS

    const IN_ALL_EVENTS = 4095







Methods
-------


### watch

    integer ZInotify::watch(string $file, integer $events)

Start watching and inode for events. Return a watch_id.



* Visibility: **public**


#### Arguments
* $file **string** - &lt;p&gt;The inode to watch.&lt;/p&gt;
* $events **integer** - &lt;p&gt;Bitwise mask of events to watch.&lt;/p&gt;



### remove

    mixed ZInotify::remove(integer $watch_id)

Stop watching watch_id.



* Visibility: **public**


#### Arguments
* $watch_id **integer** - &lt;p&gt;The watch_id returned from previous &#039;watch&#039; call.&lt;/p&gt;



### recv

    \ZMsg ZInotify::recv()

Recieve next message from the socket.



* Visibility: **public**




### get_fd

    integer IZDescriptor::get_fd()

Get the underlying File Descriptor.



* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)



