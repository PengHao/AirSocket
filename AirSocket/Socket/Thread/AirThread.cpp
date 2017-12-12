//
//  AirThread.cpp
//  kxmovie
//
//  Created by penghao on 16/1/25.
//
//

#include "AirThread.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include "AirOperation.h"
#include "AirThreadPool.h"

namespace AirCpp {
    
    void sighand(int signo){
        switch (signo) {
            case AIR_THREAD_EXIT:
                pthread_exit(0);
                break;
                case AIR_THREAD_HOLDON:
                
            default:
                break;
        }
    }
    
    void *Thread::_run_loop(void *thread) {
        Thread *_thread = (Thread *)thread;
        _thread->run_roop();
        return nullptr;
    }
    
    Thread::~Thread() {
        pthread_kill(p_id, AIR_THREAD_EXIT);
    }
    
    void Thread::run_roop() {
        while (!_cancel) {
            const Operation *oper = operation_queue->popfront_operation();
            if (oper) {
                oper->excute();
                delete oper;
            } else {
                //sleep
                pthread_cond_wait(&p_cond, &p_mutex);
            }
        }
    }
    
    void Thread::push_operation(Operation *operation) {
        operation_queue->pushOperation(operation);
        pthread_cond_signal(&p_cond);
    }
    
    int Thread::init(){
#ifndef  WIN32
        struct sigaction        actions;
        memset(&actions, 0, sizeof(actions));
        sigemptyset(&actions.sa_mask); /* 将参数set信号集初始化并清空 */
        actions.sa_flags = 0;
        actions.sa_handler = sighand;
        sigaction(AIR_THREAD_EXIT, &actions, nullptr);
#endif
        pthread_cond_init(&p_cond, NULL);
        pthread_mutex_init(&p_mutex, NULL);
        
        return pthread_create(&p_id, NULL, _run_loop, (void *)this);
    }
    
    int Thread::cancel(){
        return pthread_cancel(p_id);
    }
    
    
    void Thread::enableCancel() {
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); //允许退出线程
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL); //设置立即取消
    }
    
    void Thread::tryCancel() {
        pthread_testcancel();
    }
    
    void Thread::wait_until_done(void **ret){
        pthread_join(p_id, ret);
    }
    
    
    void Thread::keep_going(){
        pthread_detach(p_id);
    }
    
    void Thread::excute_async(Thread *thread, std::function<void()> _func) {
        Operation* o = new Operation();
        o->init(_func);
        thread->push_operation(o);
    }
    
    void Thread::excute_sync(Thread *thread, std::function<void()> _func) {
        Operation* o = new Operation();
        o->init(_func);
        thread->push_operation(o);
    }
    
    void Thread::excute_apply(int concurrence_count, std::function<void(int)> _func) {
        
        
    }
    
    void Thread::excute_after(Thread *thread, std::function<void()> _func, float after_delay) {
        Operation* o = new Operation();
        o->init([after_delay]{

#ifdef WIN32
			Sleep(after_delay*1000);
#else
			sleep(after_delay);
#endif
        });
        thread->push_operation(o);
        o = new Operation();
        o->init(_func);
        thread->push_operation(o);
    }
    
    void Thread::excute_barrier_async(Thread *thread, std::function<void()> _func) {
        
    }
    
    void Thread::excute_barrier_sync(Thread *thread, std::function<void()> _func) {
        
    }
}
