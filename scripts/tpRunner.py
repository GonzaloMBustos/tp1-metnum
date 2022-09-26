import subprocess


class TpRunner(object):
    TIMES_SEPARATOR = '==TIME VALUES==\n'

    def __init__(self, binary_path):
        self._binary_path = binary_path
        self.output = ''
        self.times = []

    def _extract_times(self, output):
        times = output.strip().split(self.TIMES_SEPARATOR)[1]
        return [int(t) for t in times.split('\n')]

    def run_test(self, matrix_size, iterations=100, warmup_iterations=100, fill_percentage=1, p=1, epsilon=0.00001,
                 times=1):
        final_output = ''
        final_times = []
        for i in range(times):
            temp_output = self.run(
                ['test',
                 str(matrix_size),
                 str(iterations),
                 str(warmup_iterations),
                 str(fill_percentage),
                 str(p),
                 str(epsilon)])
            final_output += temp_output
            final_times += self._extract_times(temp_output)
        self.times = final_times
        self.output = final_output

    def run(self, args):
        self.output = ''
        args = [self._binary_path] + args
        popen = subprocess.Popen(args, stdout=subprocess.PIPE)
        self.output = popen.stdout.read().decode()
        try:
            self.times = self._extract_times(self.output)
        except:
            pass
        return self.output


if __name__ == '__main__':
    a = TpRunner('../src/tp')
    a.run(['test', '100', '100', '0', '50', '0.7', '0.0000001'])
    a.run_test(200, iterations=1, warmup_iterations=1, times=100)
    print(a.times)
