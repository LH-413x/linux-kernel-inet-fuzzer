#!/bin/sh

dir=/sys/kernel/debug/tracing

echo > ${dir}/trace
sysctl kernel.ftrace_enabled=1
echo function_graph > ${dir}/current_tracer
echo "ip6*" > ${dir}/set_ftrace_filter
echo "inet6*" >> ${dir}/set_ftrace_filter
echo "ip_*" > ${dir}/set_ftrace_filter
echo "inet*" >> ${dir}/set_ftrace_filter
echo 1 > ${dir}/tracing_on