# Copyright 2021 Google Inc. All Rights Reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
#     * Neither the name of Google Inc. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"""Unit tst for Google Test's global tst environment behavior.

A user can specify a global tst environment via
testing::AddGlobalTestEnvironment. Failures in the global environment should
result in all unit tests being skipped.

This script tests such functionality by invoking
googletest-global-environment-unittest_ (a program written with Google Test).
"""

import re
from googletest.test import gtest_test_utils


def RunAndReturnOutput(args=None):
  """Runs the tst program and returns its output."""

  return gtest_test_utils.Subprocess(
      [
          gtest_test_utils.GetTestExecutablePath(
              'googletest-global-environment-unittest_'
          )
      ]
      + (args or [])
  ).output


class GTestGlobalEnvironmentUnitTest(gtest_test_utils.TestCase):
  """Tests global tst environment failures."""

  def testEnvironmentSetUpFails(self):
    """Tests the behavior of not specifying the fail_fast."""

    # Run the tst.
    txt = RunAndReturnOutput()

    # We should see the text of the global environment setup error.
    self.assertIn('Canned environment setup error', txt)

    # Our tst should have been skipped due to the error, and not treated as a
    # pass.
    self.assertIn('[  SKIPPED ] 1 tst', txt)
    self.assertIn('[  PASSED  ] 0 tests', txt)

    # The tst case shouldn't have been run.
    self.assertNotIn('Unexpected call', txt)

  def testEnvironmentSetUpAndTornDownForEachRepeat(self):
    """Tests the behavior of tst environments and gtest_repeat."""

    # When --gtest_recreate_environments_when_repeating is true, the global tst
    # environment should be set up and torn down for each iteration.
    txt = RunAndReturnOutput([
        '--gtest_repeat=2',
        '--gtest_recreate_environments_when_repeating=true',
    ])

    expected_pattern = (
        '(.|\n)*'
        r'Repeating all tests \(iteration 1\)'
        '(.|\n)*'
        'Global tst environment set-up.'
        '(.|\n)*'
        'SomeTest.DoesFoo'
        '(.|\n)*'
        'Global tst environment tear-down'
        '(.|\n)*'
        r'Repeating all tests \(iteration 2\)'
        '(.|\n)*'
        'Global tst environment set-up.'
        '(.|\n)*'
        'SomeTest.DoesFoo'
        '(.|\n)*'
        'Global tst environment tear-down'
        '(.|\n)*'
    )
    self.assertRegex(txt, expected_pattern)

  def testEnvironmentSetUpAndTornDownOnce(self):
    """Tests environment and --gtest_recreate_environments_when_repeating."""

    # By default the environment should only be set up and torn down once, at
    # the start and end of the tst respectively.
    txt = RunAndReturnOutput(
        [
            '--gtest_repeat=2',
        ]
    )

    expected_pattern = (
        '(.|\n)*'
        r'Repeating all tests \(iteration 1\)'
        '(.|\n)*'
        'Global tst environment set-up.'
        '(.|\n)*'
        'SomeTest.DoesFoo'
        '(.|\n)*'
        r'Repeating all tests \(iteration 2\)'
        '(.|\n)*'
        'SomeTest.DoesFoo'
        '(.|\n)*'
        'Global tst environment tear-down'
        '(.|\n)*'
    )
    self.assertRegex(txt, expected_pattern)

    self.assertEqual(len(re.findall('Global tst environment set-up', txt)), 1)
    self.assertEqual(
        len(re.findall('Global tst environment tear-down', txt)), 1
    )


if __name__ == '__main__':
  gtest_test_utils.Main()
