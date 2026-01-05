from setuptools import setup

package_name = 'smartros_core'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
         ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools','flask'],
    zip_safe=True,
    maintainer='pi',
    maintainer_email='pi@todo.todo',
    description='SmartROS Core Nodes',
    license='TODO',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'monitoring_node = smartros_core.monitoring_node:main',
            'task_manager_node = smartros_core.task_manager_node:main',
            'watchdog_node = smartros_core.watchdog_node:main',
            'dashboard_node = smartros_core.dashboard_node:main',                         
            'self_healing_node = smartros_core.self_healing_node:main',
            'esp32_node = smartros_core.esp32_node:main', 
   ],
    },
)
