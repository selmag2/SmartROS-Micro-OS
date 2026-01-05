from setuptools import setup

package_name = 'smartros_launch'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    py_modules=[],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='pi',
    maintainer_email='pi@raspberry',
    description='Launch file package for SmartROS Micro-OS',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [],
    },
    data_files=[
        # Installer le launch file dans share/<package>/launch
        ('share/' + package_name + '/launch', ['launch/all_nodes.launch.py']),
        # Installer le package.xml dans share/<package>
        ('share/' + package_name, ['package.xml']),
    ],
)
